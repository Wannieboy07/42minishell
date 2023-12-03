/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 00:44:58 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/03 23:16:24 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//initialize the export environment
int	init_var_lst(void)
{
	int		i;
	char	*env_var;
	char	**vv;

	i = -1;
	while (g_minishell.envv[++i])
	{
		env_var = ft_strdup(g_minishell.envv[i]);
		if (!env_var)
			return (free_lst(&g_minishell.var_lst), 0);
		vv = var_val(env_var);
		if (!vv)
			return (free(env_var), free_lst(&g_minishell.var_lst), 0);
		free(env_var);
		if (!add2lst(&g_minishell.var_lst, vv[VAR], vv[VAL], true))
			return (free_arr(vv), free_lst(&g_minishell.var_lst), 0);
		free_arr(vv);
	}
	return (1);
}

//logical param handler for export, adding and changing variables
static int	export_handler(char **args)
{
	char	**vv;
	t_lst	*v_v;
	int		i;

	i = 0;
	while (args[++i])
	{
		if (ft_strchr(args[i], '='))
		{
			vv = var_val(args[i]);
			if (vv)
				if (!handle_var_val(vv[VAR], vv[VAL], true))
					return (0);
			free_arr(vv);
			continue ;
		}
		v_v = check_var(g_minishell.var_lst, args[i]);
		if (v_v)
			v_v->exp = true;
		else if (!v_v)
			if (!add2lst(&g_minishell.var_lst, args[i], "", true))
				return (0);
	}
	return (1);
}

//check params of export for syntax errors
static int	err_export(char **args)
{
	int	i;
	int	j;

	i = -1;
	while (args[++i])
	{
		j = 0;
		if (args[i][j] != '_' && !ft_isalpha(args[i][j]))
			return (1);
		while (args[i][++j])
			if (args[i][j] != '_' && args[i][j] != '='
				&& !ft_isalnum(args[i][j]))
				return (1);
	}
	return (0);
}

//command to manage the export environment
int	exec_export(char **args)
{
	if (args[1] == NULL)
		return (prnt_lst(g_minishell.var_lst, true), 1);
	if (err_export(args))
		return (prnt_err("export: invalid usage", NULL));
	if (!export_handler(args))
		return (0);
	return (1);
}
