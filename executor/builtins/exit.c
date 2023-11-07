/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:12:17 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/07 20:44:58 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//exit the shell in a clean way
int	exec_exit(void)
{
	if (g_minishell.ast->args[4] != '\0' && g_minishell.ast->args[4] == ' ')
		return (prnt_err("exit: invalid usage", NULL));
	if (g_minishell.ast->args[4] != '\0')
		return (prnt_err("command not found", NULL));
	free_token_lst(&g_minishell.tokens);
	free_exp_lst(g_minishell.exp_env);
	free_ast_nodes(g_minishell.ast);
	rl_clear_history();
	exit(EXIT_SUCCESS);
	return (0);
}
