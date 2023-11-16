/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:02:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/16 15:37:44 by lpeeters         ###   ########.fr       */
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

int	exec_cmd(t_node *ast)
{
	if (!ast->args)
		return (1);
	else
		return (g_minishell.exit_code = 127, 1);
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
	else if (!ft_strncmp(ast->args, "env", 3))
		return (exec_env());
	else if (!ft_strncmp(ast->args, "exit", 4))
		return (exec_exit());
	else
		return (g_minishell.exit_code = 127, 1);
}

//add variable logic, then execute builtins, then external commands
//parse linked list and execute commands
int	executor(void)
{
	char	*test;

	if (!g_minishell.ast)
		return (1);
	if (!exec_builtin(g_minishell.ast))
		return (0);
	if (g_minishell.exit_code != 127)
		return (1);
	if (!exec_cmd(g_minishell.ast))
		return (0);
	if (g_minishell.exit_code != 127)
		return (1);
	if (!var_test())
		return (0);
	test = g_minishell.ast->args;
	if (!var_val(&test))
		return (0);
	if (test)
		printf("variable value: %s\n", test);
	else if (!ft_strchr(g_minishell.ast->args, '='))
		return (prnt_err("command not found", NULL));
	return (1);
}
