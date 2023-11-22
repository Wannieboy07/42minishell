/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 00:44:58 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/22 17:19:16 by lpeeters         ###   ########.fr       */
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

//command to manage the export environment
int	exec_export(void)
{
	char	**vv;
	t_lst	*va_va;
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
		va_va = check_var(vv[VAR], g_minishell.var_lst);
		if (va_va)
			return (free_arr(vv), va_va->exp = true, 1);
		if (!add2lst(&g_minishell.var_lst, vv[VAR], vv[VAL], true))
			return (free_arr(vv), 0);
		return (free_arr(vv), 1);
	}
	va_va = check_var(var, g_minishell.var_lst);
	if (!va_va)
		return (1);
	return (va_va->exp = true, 1);
}
