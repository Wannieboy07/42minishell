/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:12:17 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/30 19:39:15 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//exit the shell in a clean way
int	exec_exit(char **args)
{
	int	status;
	int	i;

	if (args[0][4] != '\0' && args[0][4] != ' ')
		return (g_minishell.exit_code = 127,
			prnt_err("exit: invalid usage", NULL));
	if (args[0][4] == ' ' && args[0][5] == '-')
		return (prnt_err("exit: invalid usage", NULL));
	status = EXIT_SUCCESS;
	if (args[0][4] == ' ')
	{
		i = 4;
		while (args[0][++i])
			if (!ft_isdigit(args[0][i]))
				return (prnt_err("exit: invalid usage", NULL));
		status = ft_atoi(g_minishell.ast->args + 5);
		if (status > 255)
			return (prnt_err("exit: invalid usage", NULL));
	}
	free_token_lst(&g_minishell.tokens);
	free_lst(&g_minishell.var_lst);
	free_ast_nodes(g_minishell.ast);
	rl_clear_history();
	exit(status);
	return (0);
}
