/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:02:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/28 15:56:53 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//pipe redirector
static int	redir(int fd, int *pfd)
{
	if (!pfd)
		return (1);
	if (fd == IN)
		if (close(pfd[IN]) < 0 || dup2(pfd[OUT], STDOUT_FILENO) < 0)
			return (perror("redir in"), 0);
	if (fd == OUT)
		if (close(pfd[OUT]) < 0 || (dup2(pfd[IN], STDIN_FILENO) < 0))
			return (perror("redir out"), 0);
	return (1);
}

//logical piping handler
static int	pipe_handler(t_node *ast, int fd, int *pfd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 0);
	if (!pid)
	{
		if (fd != -1)
			if (!redir(fd, pfd))
				exit(EXIT_FAILURE);
		exec_ext(ast->exp_args);
		exit(EXIT_FAILURE);
	}
	if (fd == OUT)
		if (close(pfd[IN]) < 0 || close(pfd[OUT]) < 0)
			return (perror("close"), 0);
	waitpid(pid, &status, 0);
	if (status != 0)
		return (status);
	return (0);
}

//execute external commands
int	exec_cmd(t_node *ast)
{
	int	pfd[2];
	int	status;

	if (!ast)
		return (1);
	if (ast->type == P_PIPE)
	{
		if (pipe(pfd) < 0)
			return (perror("pipe"), 0);
		status = pipe_handler(ast->left, IN, pfd);
		if (status != 0)
			return (prnt_err("cmd", NULL), 0);
		status = pipe_handler(ast->right, OUT, pfd);
		if (status != 0)
			return (prnt_err("cmd", NULL), 0);
		return (g_minishell.exit_code = 0, 1);
	}
	else
	{
		if (!pipe_handler(ast, -1, NULL))
			return (0);
		return (g_minishell.exit_code = 0, 1);
	}
}

//execute built-in commands
int	exec_builtin(t_node *ast)
{
	if (!ast->args)
		return (g_minishell.exit_code = 127, 1);
	if (!ft_strncmp(ast->args, "echo", 4))
		return (exec_echo());
	else if (!ft_strncmp(ast->args, "cd", 2))
		return (exec_cd());
	else if (!ft_strncmp(ast->args, "pwd", 3))
		return (exec_pwd());
	else if (!ft_strncmp(ast->args, "export", 6))
		return (exec_export());
	else if (!ft_strncmp(ast->args, "unset", 5))
		return (exec_unset());
	else if (!ft_strncmp(ast->args, "set", 3))
		return (exec_set());
	else if (!ft_strncmp(ast->args, "env", 3))
		return (exec_env());
	else if (!ft_strncmp(ast->args, "exit", 4))
		return (exec_exit());
	else
		return (g_minishell.exit_code = 127, 1);
}

//parse linked list and execute commands
int	executor(void)
{
	if (!g_minishell.ast)
		return (1);
	g_minishell.exit_code = 0;
	if (!var_handler(g_minishell.ast->args))
		return (g_minishell.exit_code);
	if (g_minishell.exit_code != 127)
		return (1);
	g_minishell.exit_code = 0;
	if (!exec_builtin(g_minishell.ast))
		return (g_minishell.exit_code);
	if (g_minishell.exit_code != 127)
		return (1);
	if (!exec_cmd(g_minishell.ast))
		return (g_minishell.exit_code);
	if (g_minishell.exit_code != 127)
		return (1);
	return (prnt_err("command not found", NULL), 1);
}
