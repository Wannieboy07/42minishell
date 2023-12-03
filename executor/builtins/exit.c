/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:12:17 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/03 21:12:13 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//exit the shell in a clean way
int	exec_exit(char **args)
{
	int	status;
	int	i;

	if (args[1] != NULL && args[2] != NULL)
		return (prnt_err("exit: invalid usage", NULL));
	status = EXIT_SUCCESS;
	if (args[1] != NULL)
	{
		i = -1;
		while (args[1][++i])
			if (!ft_isdigit(args[1][i]))
				return (prnt_err("exit: invalid usage", NULL));
		status = ft_atoi(args[1]);
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
