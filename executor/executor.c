/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:02:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/25 22:05:06 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

////tester function
//static void	prnt_ast_testing(t_node *ast)
//{
	//int	i;

	//if (!ast)
	//{
		//printf("Info: no ast\n");
		//return ;
	//}
	//while (ast->left)
		//ast = ast->left;
	//i = 0;
	//printf("%i: %s\n", i, ast->args);
	//i += 1;
	//while (ast->right)
	//{
		//ast = ast->right;
		//printf("%i: %s\n", i, ast->args);
		//i += 1;
	//}
//}

////tester function
//static void	prnt_nxt_in_ast(t_node *ast)
//{
	//if (ast->right)
	//{
		//ast = ast->right;
		//printf("test: %s\n", ast->args);
	//}
//}

//pipe redirector
static int	redir(int fd, int *pfd)
{
	if (!fd || !pfd)
		return (1);
	if (fd == IN)
	{
		if (close(pfd[OUT]) < 0)
			return (0);
		if (dup2(pfd[IN], STDIN_FILENO) < 0)
			return (0);
	}
	else if (fd == OUT)
	{
		if (close(pfd[IN]) < 0)
			return (0);
		if (dup2(pfd[OUT], STDOUT_FILENO) < 0)
			return (0);
	}
	return (1);
}

//logical piping handler
static int	pipe_handler(int *pfd, t_node *ast)
{
	pid_t	pid;
	int		status;

	if (pipe(pfd) < 0)
		return (0);
	pid = fork();
	if (pid < 0)
		return (0);
	if (!pid)
	{
		if (!redir(IN, pfd))
			return (0);
		ast = ast->left;
		exec_ext(ast->exp_args);
		waitpid(pid, &status, 0);
		if (status != 0)
			return (0);
	}
	else
	{
		ast = ast->right;
		if (!redir(OUT, pfd))
			return (0);
		exec_ext(ast->exp_args);
	}
	return (1);
}

//execute external commands
int	exec_cmd(t_node *ast)
{
	int	pfd[2];

	if (!ast)
		return (1);
	if (ast->type == P_PIPE)
	{
		if (!pipe_handler(pfd, ast))
			return (0);
		return (1);
	}
	if (!exec_ext(ast->exp_args))
		return (0);
	return (1);
}

//execute built-in commands
int	exec_builtin(t_node *ast)
{
	if (!ast->args)
		return (1);
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
	//g_minishell.exit_code = 0;
	//if (!exec_builtin(g_minishell.ast))
		//return (0);
	//if (g_minishell.exit_code != 127)
		//return (1);
	g_minishell.exit_code = 0;
	if (!exec_cmd(g_minishell.ast))
		return (0);
	if (g_minishell.exit_code != 127)
		return (1);
	g_minishell.exit_code = 0;
	if (!var_handler(g_minishell.ast->args))
		return (0);
	if (g_minishell.exit_code != 127)
		return (1);
	return (prnt_err("command not found", NULL), 1);
}
