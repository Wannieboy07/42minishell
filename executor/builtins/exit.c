/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:12:17 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/21 21:43:10 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//exit the shell in a clean way
int	exec_exit(void)
{
	int	status;
	int	i;

	if (g_minishell.ast->args[4] != '\0' && g_minishell.ast->args[4] != ' ')
		return (g_minishell.exit_code = 127,
			prnt_err("exit: invalid usage", NULL));
	if (g_minishell.ast->args[4] == ' ' && g_minishell.ast->args[5] == '-')
		return (prnt_err("exit: invalid usage", NULL));
	status = EXIT_SUCCESS;
	if (g_minishell.ast->args[4] == ' ')
	{
		i = 4;
		while (g_minishell.ast->args[++i])
			if (!ft_isdigit(g_minishell.ast->args[i]))
				return (prnt_err("exit: invalid usage", NULL));
		status = ft_atoi(g_minishell.ast->args + 5);
	}
	free_token_lst(&g_minishell.tokens);
	free_lst(&g_minishell.var_lst);
	free_ast_nodes(g_minishell.ast);
	rl_clear_history();
	exit(status);
	return (0);
}
