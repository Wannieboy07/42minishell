/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 00:44:58 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/01 01:59:16 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//WIP
//print out the export environment variable
int	exec_export(void)
{
	int			i;

	if (!g_minishell.exp_env)
	{
		printf("test\n");
		g_minishell.exp_env = init_exp_lst(g_minishell.envv[0]);
		if (!g_minishell.exp_env)
			return (0);
		i = 0;
		while (g_minishell.envv[++i])
			if (!add_val2exp_lst(g_minishell.exp_env, g_minishell.envv[i]))
				return (0);
	}
	if (ft_strncmp(g_minishell.ast->args, "export ", 7))
		prnt_exp_lst(g_minishell.exp_env);
	else if (!ft_strncmp(g_minishell.ast->args, "export -", 8)
		|| !ft_strchr(g_minishell.ast->args, '='))
		prnt_err("export: invalid usage", NULL);
	else
	{
		printf("test0\n");
		add_val2exp_lst(g_minishell.exp_env, g_minishell.ast->args + 7);
	}
	return (1);
}
