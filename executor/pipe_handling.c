/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:01:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/01 21:48:37 by lpeeters         ###   ########.fr       */
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
static int	exec_cmd(int fd, int *pfd, t_node *ast, char *path)
{
	if (fd == IN)
		if (!pipe_redir(IN, pfd))
			return (free(path), exit(EXIT_FAILURE), 0);
	g_minishell.exit_code = 0;
	if (!exec_builtin(ast->exp_args))
		return (free(path), exit(EXIT_FAILURE), 0);
	if (g_minishell.exit_code != 127)
		return (free(path), exit(EXIT_SUCCESS), 1);
	else
		exec_ext(ast->exp_args, path);
	return (free(path), exit(EXIT_FAILURE), 0);
}
//info: builtins currently do not work with pipes

//handle redirection after child
static int	parent(int fd, int *pfd, pid_t pid, char *path)
{
	waitpid(pid, &g_minishell.exit_code, 0);
	if (fd == IN)
	{
		if (close(pfd[OUT]) < 0)
			return (free(path), perror("close"), 0);
		if (!pipe_redir(OUT, pfd))
			return (free(path), 0);
	}
	return (free(path), 1);
}
	//else if (fd == OUT)
		//if (dup2(g_minishell.fdin, STDIN_FILENO) < 0
			//|| close(g_minishell.fdin) < 0)
			//return (perror("error resetting input"), 0);
//info: In the function above, leaving out the else if will make single
//commands work for an infinite amount, but with pipes, the shell exits.
//On the other hand, leaving it in will make everything work, only for
//2 times any command and amount of them is ran in the shell, even pipes.

//logical piping handler
int	pipe_handler(t_node *ast, int fd)
{
	pid_t	pid;
	char	*path;
	int		pfd[2];

	path = check_path(ast->exp_args[0]);
	if (!path)
		return (prnt_err("command not found", NULL), 0);
	if (pipe(pfd) > 0)
		return (free(path), perror("pipe"), 0);
	pid = fork();
	if (pid < 0)
		return (free(path), perror("fork"), 0);
	if (pid == CHILD)
		return (exec_cmd(fd, pfd, ast, path));
	else
		return (parent(fd, pfd, pid, path));
	return (free(path), 0);
}
