/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:02:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/29 19:27:03 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*//execute external commands*/
/*int	exec_cmd(t_node *ast)*/
/*{*/
	/*if (!ast)*/
		/*return (1);*/
	/*if (ast->type == P_PIPE)*/
	/*{*/
		/*if (!ast_parser(ast, -1))*/
			/*return (0);*/
	/*}*/
	/*else*/
	/*{*/
		/*if (!pipe_handler(ast, -1, NULL))*/
			/*return (0);*/
	/*}*/
	/*if (g_minishell.exit_code != 0)*/
		/*return (prnt_err("could not execute command", NULL), 0);*/
	/*return (1);*/
/*}*/

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

//execute commands in order
int	ast_parser(t_node *ast, int fd, t_node *start, int *pfd)
{
	if (!ast)
		return (0);
	if (ast->type == P_PIPE)
	{
		if (ast->left)
			ast_parser(ast->left, IN, start, pfd);
		if (ast->right != start->right)
			ast_parser(ast->right, IN, start, pfd);
		if (ast->right == start->right)
			ast_parser(ast->right, OUT, start, pfd);
	}
	else if (ast->type == P_CMD)
	{
		printf("cmd: %s\n", ast->exp_args[0]);
		if (!pipe_handler(ast, fd, pfd))
			return (0);
		if (g_minishell.exit_code != 0)
			return (prnt_err("could not execute command", NULL), 0);
	}
	return (1);
}

//parse linked list and execute commands
int	executor(void)
{
	int		pfd[2];

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
	if (pipe(pfd) < 0)
		return (perror("pipe"), 0);
	if (!ast_parser(g_minishell.ast, -1, g_minishell.ast, pfd))
		return (g_minishell.exit_code);
	if (g_minishell.exit_code != 127)
		return (1);
	return (prnt_err("command not found", NULL), 1);
}
