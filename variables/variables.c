/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:17:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/14 19:24:53 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//fetch the variable a variable list entree
char	*extract_var(char *lst_val)
{
	char	*var;
	int		i;

	if (!lst_val || !ft_strchr(lst_val, '='))
		return (NULL);
	i = 0;
	while (lst_val[i++])
		if (lst_val[i] == '=')
			break ;
	var = (char *)malloc(sizeof(char) * i + 1);
	if (!var)
		return (NULL);
	var[i] = '\0';
	while (--i > -1)
		var[i] = lst_val[i];
	return (var);
}

//search for a variable's value inside the variable list
char	*var_val(char *var)
{
	t_lst	*var_lst;
	char	*lst_var;
	char	*val;

	if (!var || !g_minishell.var_lst)
		return (NULL);
	var_lst = g_minishell.var_lst;
	while (var_lst)
	{
		val = NULL;
		lst_var = extract_var(var_lst->val);
		if (!lst_var)
			return (0);
		if (ft_strlen(var) == ft_strlen(lst_var)
			&& !ft_strncmp(lst_var, var, ft_strlen(lst_var)))
		{
			val = ft_strdup(ft_strchr(var_lst->val, '=') + 1);
			if (!val)
				return (NULL);
		}
		if (val != NULL)
			return (val);
		var_lst = var_lst->next;
	}
	return (NULL);
}

//WIP
//currently just testing
int	var_test(void)
{
	if (!ft_strchr(g_minishell.ast->args, '='))
		return (1);
	if (!check_var(g_minishell.ast->args, g_minishell.var_lst))
		return (add2lst(&g_minishell.var_lst, g_minishell.ast->args));
	return (1);
}
