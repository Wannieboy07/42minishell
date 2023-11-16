/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:17:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/16 18:40:16 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	*lst_val = var;
	return (1);
}

//search for a variable's value inside the variable list
int	var_val(char **var)
{
	t_lst	*var_lst;
	char	*lst_var;
	char	*val;

	if (!*var || !g_minishell.var_lst)
		return (1);
	var_lst = g_minishell.var_lst;
	while (var_lst)
	{
		lst_var = var_lst->val;
		if (!extract_var(&lst_var))
			return (0);
		if (!lst_var)
			return (*var = NULL, 1);
		val = NULL;
		if (ft_strlen(*var) == ft_strlen(lst_var)
			&& !ft_strncmp(lst_var, *var, ft_strlen(lst_var)))
		{
			val = ft_strdup(ft_strchr(var_lst->val, '=') + 1);
			if (!val)
				return (free(lst_var), 0);
		}
		if (val != NULL)
			return (*var = val, 1);
		var_lst = var_lst->next;
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
