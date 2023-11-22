/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 00:44:58 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/22 19:45:08 by lpeeters         ###   ########.fr       */
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

//check argument's string for syntax errors
static int	err_arg(char *str)
{
	int	i;

	if (str[6] != '\0' && str[6] != ' ')
		return (g_minishell.exit_code = 127, 1);
	if (str[7] == '=')
		return (prnt_err("export: invalid usage", NULL));
	i = 6;
	while (str[++i])
		if (str[i] != '=' && !ft_isalpha(str[i]))
			return (prnt_err("export: invalid usage", NULL));
	return (0);
}

//WIP
//check if variable exists and change value if it needs to be changed
static int	check_var_val(char *var, char *val)
{
	t_lst	*vv;

	vv = check_var(var, g_minishell.var_lst);
	if (!vv)
		return (0);
	if (ft_strlen(vv->val) == ft_strlen(val)
		&& !ft_strncmp(vv->val, val, ft_strlen(vv->val)))
		return (1);
	return (0);
}

//command to manage the export environment
int	exec_export(void)
{
	char	**vv;
	t_lst	*v_v;
	char	*var;

	if (g_minishell.ast->args[6] == '\0')
		return (prnt_lst(g_minishell.var_lst, true), 1);
	if (err_arg(g_minishell.ast->args))
		return (1);
	var = g_minishell.ast->args + 7;
	if (ft_strchr(var, '='))
	{
		vv = var_val(var);
		if (!vv)
			return (0);
		v_v = check_var(vv[VAR], g_minishell.var_lst);
		if (v_v)
			return (free_arr(vv), v_v->exp = true, 1);
		if (!add2lst(&g_minishell.var_lst, vv[VAR], vv[VAL], true))
			return (free_arr(vv), 0);
		return (free_arr(vv), 1);
	}
	v_v = check_var(var, g_minishell.var_lst);
	if (!v_v)
		return (1);
	return (v_v->exp = true, 1);
}
