/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:17:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/04 15:40:17 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//check if variable exists and change value if it needs to be changed
int	handle_var_val(char *var, char *val, bool exp)
{
	t_lst	*vv;

	vv = check_var(g_minishell.var_lst, var);
	if (!vv)
	{
		if (!add2lst(&g_minishell.var_lst, var, val, exp))
			return (0);
		return (1);
	}
	if (ft_strlen(val) == ft_strlen(vv->val)
		&& !ft_strncmp(val, vv->val, ft_strlen(val)))
		return (vv->exp = exp, 1);
	free(vv->val);
	vv->val = NULL;
	vv->val = ft_strdup(val);
	if (!vv->val)
		return (0);
	return (1);
}

//check whether a value matches for a variable within the environment
t_lst	*check_val(t_lst *lst, char *val)
{
	t_lst	*curr;

	if (!val || !lst)
		return (NULL);
	curr = lst;
	while (curr)
	{
		if (ft_strlen(val) == ft_strlen(curr->val)
			&& !ft_strncmp(val, curr->val, ft_strlen(val)))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

//check whether a variable exists within the environment
t_lst	*check_var(t_lst *lst, char *var)
{
	t_lst	*curr;

	if (!var || !lst)
		return (NULL);
	curr = lst;
	while (curr)
	{
		if (ft_strlen(var) == ft_strlen(curr->var)
			&& !ft_strncmp(var, curr->var, ft_strlen(var)))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

//convert variable string to array
char	**var_val(char *var_val)
{
	char	*var;
	char	*val;

	if (!var_val)
		return (NULL);
	var = var_val;
	val = ft_strchr(var_val, '=') + 1;
	ft_strlcpy(var, var_val, (ft_strlen(var_val) - ft_strlen(val)));
	return (mk_arr(var, val));
}

//logical variable handler
int	var_handler(char **args)
{
	char	**vv;
	int		i;

	if (!args || !ft_strchr(args[0], '='))
		return (g_minishell.exit_code = 127, 1);
	i = -1;
	while (args[++i])
	{
		if (err_var(args[i]))
		{
			prnt_arg_err("variable", args[i], "syntax error");
			continue ;
		}
		vv = var_val(args[i]);
		if (!vv)
			return (0);
		if (!handle_var_val(vv[VAR], vv[VAL], false))
			return (free_arr(vv), 0);
		free_arr(vv);
	}
	return (1);
}
