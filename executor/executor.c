/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:02:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/07 20:40:55 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*//tester function*/
/*static void	prnt_ast_testing(t_node *ast)*/
/*{*/
	/*int	i;*/

	/*if (!ast)*/
	/*{*/
		/*printf("Info: no ast\n");*/
		/*return ;*/
	/*}*/
	/*while (ast->left)*/
		/*ast = ast->left;*/
	/*i = 0;*/
	/*printf("%i: %s\n", i, ast->args);*/
	/*i += 1;*/
	/*while (ast->right)*/
	/*{*/
		/*ast = ast->right;*/
		/*printf("%i: %s\n", i, ast->args);*/
		/*i += 1;*/
	/*}*/
/*}*/

/*//tester function*/
/*static void	prnt_nxt_in_ast(t_node *ast)*/
/*{*/
	/*if (ast->right)*/
	/*{*/
		/*ast = ast->right;*/
		/*printf("test: %s\n", ast->args);*/
	/*}*/
/*}*/

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
		return (prnt_err("command not found", NULL));
}

//add pipex logic to run before builtins:
//if (!exec_ext_cmd && !exec_builtin)
//{
		//prnt_err("command not found", NULL);
		//return (0);
//}

//execute commands if any are found
int	exec_cmd(t_node *ast)
{
	if (!ast)
	{
		printf(GREY "Info: nothing to execute\n" WHITE);
		return (1);
	}
	if (!exec_builtin(ast))
		return (0);
	return (1);
}

//parse linked list and execute commands
int	executor(void)
{
	if (!exec_cmd(g_minishell.ast))
		return (0);
	return (1);
}
