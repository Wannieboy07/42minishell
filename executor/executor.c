/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:02:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/24 21:08:42 by lpeeters         ###   ########.fr       */
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

//execute external commands
int	exec_cmd(t_node *ast)
{
	if (!ast->exp_args)
		return (1);
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
	g_minishell.exit_code = 0;
	if (!exec_builtin(g_minishell.ast))
		return (0);
	if (g_minishell.exit_code != 127)
		return (1);
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
