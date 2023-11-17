/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 00:44:58 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/17 18:11:06 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//initialize the export environment
int	init_exp_env(void)
{
	int			i;

	i = 0;
	if (!g_minishell.exp_env)
		while (g_minishell.envv[i])
			if (!add2lst(&g_minishell.exp_env, g_minishell.envv[i++]))
				return (free_lst(g_minishell.exp_env), 0);
	return (1);
}

//command to manage the export environment
int	exec_export(void)
{
	char	*var;

	if (g_minishell.ast->args[6] != '\0' && g_minishell.ast->args[6] != ' ')
		return (g_minishell.exit_code = 127, 1);
	if (g_minishell.ast->args[6] == '\0')
		return (prnt_lst(g_minishell.exp_env), 1);
	if (g_minishell.ast->args[6] != ' ' || g_minishell.ast->args[7] == '-')
		return (prnt_err("export: invalid usage", NULL));
	if (ft_strchr(g_minishell.ast->args, '='))
		return (add2lst(&g_minishell.exp_env, g_minishell.ast->args + 7),
			add2lst(&g_minishell.var_lst, g_minishell.ast->args + 7));
	var = g_minishell.ast->args + 7;
	if (!var_val(&var, g_minishell.var_lst))
		return (free(var), 0);
	if (!var)
		return (1);
	if (!complete_var(&var))
		return (free(var), 0);
	if (!var)
		return (1);
	if (!add2lst(&g_minishell.exp_env, var)
		|| !add2lst(&g_minishell.var_lst, var))
		return (free(var), 0);
	return (free(var), 1);
}
