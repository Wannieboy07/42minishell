/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:02:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/04 17:31:11 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//execute built-in commands
int	exec_builtin(char **args)
{
	if (!args)
		return (g_minishell.exit_code = 127, 1);
	if (!ft_strcmp(args[0], "echo"))
		return (exec_echo(args));
	else if (!ft_strcmp(args[0], "cd"))
		return (exec_cd(args));
	else if (!ft_strcmp(args[0], "pwd"))
		return (exec_pwd(args));
	else if (!ft_strcmp(args[0], "export"))
		return (exec_export(args));
	else if (!ft_strcmp(args[0], "unset"))
		return (exec_unset(args));
	else if (!ft_strcmp(args[0], "set"))
		return (exec_set(args));
	else if (!ft_strcmp(args[0], "env"))
		return (exec_env(args));
	else if (!ft_strcmp(args[0], "exit"))
		return (exec_exit(args));
	else
		return (g_minishell.exit_code = 127, 1);
}

//execute commands in order
int	ast_parser(t_node *start, t_node *ast, int fd)
{
	if (!start || !ast)
		return (1);
	if (ast->type == P_PIPE)
	{
		if (ast->left)
			ast_parser(start, ast->left, IN);
		if (ast->right != start->right)
			ast_parser(start, ast->right, IN);
		if (ast->right == start->right)
			ast_parser(start, ast->right, OUT);
	}
	else if (ast->type == P_CMD)
	{
		if (!pipe_handler(ast, fd))
			return (0);
		if (g_minishell.exit_code != 0)
			return (prnt_err("could not execute command", NULL), 0);
	}
	return (1);
}

//parse linked list and execute commands
int	executor(void)
{
	if (!g_minishell.ast)
		return (1);
	g_minishell.exit_code = 0;
	if (!var_handler(g_minishell.ast->exp_args))
		return (0);
	if (g_minishell.exit_code != 127)
		return (1);
	if (g_minishell.ast->type == P_CMD)
	{
		g_minishell.exit_code = 0;
		if (!exec_builtin(g_minishell.ast->exp_args))
			return (0);
		if (g_minishell.exit_code != 127)
			return (1);
	}
	g_minishell.exit_code = 0;
	if (!ast_parser(g_minishell.ast, g_minishell.ast, OUT))
		return (g_minishell.exit_code);
	if (g_minishell.exit_code != 127)
		return (1);
	return (prnt_err("command not found", NULL), 1);
}
