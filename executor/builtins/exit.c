/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:12:17 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/01 02:04:23 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//exit the shell in a clean way
void	exec_exit(void)
{
	free_token_lst(&g_minishell.tokens);
	free_exp_lst(g_minishell.exp_env);
	free_ast_nodes(g_minishell.ast);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
