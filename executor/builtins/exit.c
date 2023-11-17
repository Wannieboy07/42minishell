/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:12:17 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/17 21:15:22 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//exit the shell in a clean way
int	exec_exit(void)
{
	if (g_minishell.ast->args[4] != '\0' && g_minishell.ast->args[4] == ' ')
		return (prnt_err("exit: invalid usage", NULL));
	if (g_minishell.ast->args[4] != '\0')
		return (g_minishell.exit_code = 127, 1);
	free_token_lst(&g_minishell.tokens);
	free_lst(g_minishell.exp_env);
	free_lst(g_minishell.var_lst);
	free_ast_nodes(g_minishell.ast);
	rl_clear_history();
	exit(EXIT_SUCCESS);
	return (0);
}
