/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 00:44:58 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/03 23:04:24 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//initialize the export environment
int	init_exp_env(void)
{
	int			i;

	if (!g_minishell.exp_env)
	{
		g_minishell.exp_env = init_exp_lst(g_minishell.envv[0]);
		if (!g_minishell.exp_env)
			return (0);
		i = 1;
		while (g_minishell.envv[i])
			if (!add_val2exp_lst(g_minishell.exp_env, g_minishell.envv[i++]))
				return (free_exp_lst(g_minishell.exp_env), 0);
	}
	return (1);
}

//Variables not yet implemented.
//command to manage the export environment
int	exec_export(void)
{
	if (ft_strncmp(g_minishell.ast->args, "export ", 7))
		prnt_exp_lst(g_minishell.exp_env);
	else if (!ft_strncmp(g_minishell.ast->args, "export -", 8)
		|| !ft_strchr(g_minishell.ast->args, '='))
		prnt_err("export: invalid usage", NULL);
	else
		add_val2exp_lst(g_minishell.exp_env,
			ft_strdup(g_minishell.ast->args + 7));
	return (1);
}
