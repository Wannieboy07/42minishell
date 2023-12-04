/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:12:17 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/04 18:59:53 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//exit the shell in a clean way
int	exec_exit(char **args)
{
	int	i;
	int	status;

	if (args[1] != NULL && args[2] != NULL)
		return (prnt_arg_err("exit", NULL, "too many arguments"));
	status = EXIT_SUCCESS;
	if (args[1] != NULL)
	{
		i = -1;
		if (args[1][0] == '+' || args[1][0] == '-')
			i = 0;
		while (args[1][++i])
			if (!ft_isdigit(args[1][i]))
				return (prnt_arg_err("exit", NULL, "not numeric"));
		status = ft_atoi(args[1]);
		if (0 > status || status > 255 || ft_strlen(args[1]) > 9)
			return (prnt_arg_err("exit", NULL, "out of scope"));
	}
	free_token_lst(&g_minishell.tokens);
	free_lst(&g_minishell.var_lst);
	free_ast_nodes(g_minishell.ast);
	rl_clear_history();
	exit(status);
	return (0);
}
