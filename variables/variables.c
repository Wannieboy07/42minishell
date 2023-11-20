/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:17:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/20 23:59:43 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//populate an entree to a data list
int	complete_var(char **val)
{
	char	*var;
	char	*var_eq;
	char	*var_completed;

	if (!*val)
		return (1);
	var = ft_strdup(ft_strchr(g_minishell.ast->args, ' ') + 1);
	if (!var)
		return (0);
	var_eq = ft_strjoin(var, "=");
	if (!var_eq)
		return (free(var), 0);
	var_completed = ft_strjoin(var_eq, *val);
	if (!var_completed)
		return (free(var_eq), 0);
	return (*val = var_completed, 1);
}

//fetch the variable a variable list entree
int	extract_var(char **lst_val)
{
	char	*var;
	int		i;

	if (!*lst_val || !ft_strchr(*lst_val, '='))
		return (1);
	i = 0;
	while ((*lst_val)[i++])
		if ((*lst_val)[i] == '=')
			break ;
	var = (char *)malloc(sizeof(char) * (i + 1));
	if (!var)
		return (0);
	var[i] = '\0';
	while (--i > -1)
		var[i] = (*lst_val)[i];
	return (*lst_val = var, 1);
}

//check if variable exists within list
static int	var_exists(char **var, char **lst_var, char *lst_val)
{
	char	*val;

	val = NULL;
	if (ft_strlen(*var) == ft_strlen(*lst_var)
		&& !ft_strncmp(*lst_var, *var, ft_strlen(*lst_var)))
	{
		val = ft_strchr(lst_val, '=') + 1;
		if (!val)
			return (free(*lst_var), 0);
	}
	if (val != NULL)
		return (free(*lst_var), *var = val, 1);
	return (free(*lst_var), *var = NULL, 1);
}

//search for a variable's value inside a variable list
int	var_val(char **var, t_lst *lst)
{
	char	*lst_var;
	char	*hold_var;

	if (!*var)
		return (1);
	if (!lst)
		return (*var = NULL, 1);
	hold_var = *var;
	while (lst)
	{
		lst_var = lst->val;
		if (!extract_var(&lst_var))
			return (0);
		if (!lst_var)
			return (*var = NULL, 1);
		if (!var_exists(var, &lst_var, lst->val))
			return (0);
		if (var != NULL)
			return (1);
		*var = hold_var;
		lst = lst->next;
	}
	return (*var = NULL, 1);
}

//ready to be implemented
int	var_test(void)
{
	if (!ft_strchr(g_minishell.ast->args, '='))
		return (1);
	if (!check_var(g_minishell.ast->args, g_minishell.var_lst))
		return (add2lst(&g_minishell.var_lst, g_minishell.ast->args));
	return (1);
}
