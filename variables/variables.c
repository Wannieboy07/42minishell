/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:17:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/22 00:26:50 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//check whether a variable exists within the environment
t_lst	*check_var(char *var, t_lst *lst)
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
	val = ft_strchr(var_val, '=') + 1;
	var = var_val;
	ft_strlcpy(var, var_val, (ft_strlen(var_val) - ft_strlen(val)));
	return (mk_arr(var, val));
}

//logical variable handler
int	var_handler(char *args)
{
	char	**vv;

	if (!ft_strchr(args, '='))
		return (g_minishell.exit_code = 127, 1);
	vv = var_val(args);
	if (!vv)
		return (0);
	if (!add2lst(&g_minishell.var_lst, vv[VAR], vv[VAL], false))
		return (0);
	return (free_arr(vv), prnt_lst(g_minishell.var_lst, false), 1);
}
