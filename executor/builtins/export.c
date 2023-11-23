/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 00:44:58 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/23 14:08:11 by lpeeters         ###   ########.fr       */
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
	if (str[6] != '\0' && str[6] != ' ')
		return (g_minishell.exit_code = 127, 1);
	if (str[7] == '=' && !ft_isalpha(str[7]))
		return (prnt_err("export: invalid usage", NULL));
	return (0);
}

//check if variable exists and change value if it needs to be changed
static int	handle_var_val(char *var, char *val)
{
	t_lst	*vv;

	vv = check_var(g_minishell.var_lst, var);
	if (!vv)
	{
		if (!add2lst(&g_minishell.var_lst, var, val, true))
			return (0);
		return (1);
	}
	if (ft_strlen(val) == ft_strlen(vv->val)
		&& !ft_strncmp(val, vv->val, ft_strlen(val)))
		return (vv->exp = true, 1);
	free(vv->val);
	vv->val = NULL;
	vv->val = ft_strdup(val);
	if (!vv->val)
		return (0);
	return (1);
}

//command to manage the export environment
int	exec_export(void)
{
	char	**vv;
	t_lst	*v_v;

	if (g_minishell.ast->args[6] == '\0')
		return (prnt_lst(g_minishell.var_lst, true), 1);
	if (err_arg(g_minishell.ast->args))
		return (1);
	if (ft_strchr(g_minishell.ast->args + 7, '='))
	{
		vv = var_val(g_minishell.ast->args + 7);
		if (!vv)
			return (1);
		if (!handle_var_val(vv[VAR], vv[VAL]))
			return (0);
		return (free_arr(vv), 1);
	}
	v_v = check_var(g_minishell.var_lst, g_minishell.ast->args + 7);
	if (!v_v)
		return (1);
	return (v_v->exp = true, 1);
}
