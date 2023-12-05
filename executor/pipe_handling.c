/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:01:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/05 13:45:30 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//pipe redirector
static int	pipe_redir(int fd, int *pfd)
{
	if (!pfd)
		return (1);
	if (fd == IN)
		if (close(pfd[IN]) < 0 || dup2(pfd[OUT], STDOUT_FILENO) < 0
			|| close(pfd[OUT]) < 0)
			return (perror("redir in"), 0);
	if (fd == OUT)
		if (dup2(pfd[IN], STDIN_FILENO) < 0
			|| close(pfd[IN]) < 0)
			return (perror("redir out"), 0);
	return (1);
}

//execute commands within child process
static int	exec_cmd(int fd, int *pfd, t_node *ast)
{
	char	*path;

	if (fd == IN)
		if (!pipe_redir(IN, pfd))
			return (exit(EXIT_FAILURE), 0);
	g_minishell.exit_code = 0;
	if (!exec_builtin(ast->exp_args))
		return (exit(EXIT_FAILURE), 0);
	if (g_minishell.exit_code != 127)
		return (exit(EXIT_SUCCESS), 1);
	path = check_path(ast->exp_args[0]);
	if (!path)
		return (prnt_err("command not found", NULL), exit(EXIT_FAILURE), 0);
	exec_ext(ast->exp_args, path);
	return (free(path), exit(EXIT_FAILURE), 0);
}
//info: builtins currently do not work with pipes

//handle redirection after child
static int	parent(int fd, int *pfd, pid_t pid)
{
	waitpid(pid, &g_minishell.exit_code, 0);
	if (g_minishell.exit_code > 255)
		g_minishell.exit_code %= 255;
	if (fd == IN)
	{
		if (close(pfd[OUT]) < 0)
			return (perror("close"), 0);
		if (!pipe_redir(OUT, pfd))
			return (0);
	}
	else if (fd == OUT)
		if (dup2(g_minishell.fdin, STDIN_FILENO) < 0)
			return (perror("error resetting input"), 0);
	return (1);
}

//logical piping handler
int	pipe_handler(t_node *ast, int fd)
{
	pid_t	pid;
	int		pfd[2];

	if (pipe(pfd) > 0)
		return (perror("pipe"), 0);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 0);
	if (pid == CHILD)
		return (exec_cmd(fd, pfd, ast));
	else
		return (parent(fd, pfd, pid));
	return (0);
}
