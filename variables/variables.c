/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:17:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/13 18:30:08 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//search for a variable's value inside the variable list
char	*var_val(char *var)
{
	t_lst	*vl;
	char	*val;

	if (!var || !g_minishell.var_lst)
		return (NULL);
	vl = g_minishell.var_lst;
	while (vl)
	{
		if (!ft_strncmp(vl->val, var, ft_strlen(vl->val)))
		{
			val = NULL;
			val = ft_strdup(ft_strnstr(vl->val, "=", ft_strlen(vl->val)) + 1);
			if (!val)
				return (NULL);
		}
		if (val != NULL)
			return (val);
		vl = vl->next;
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
	{
		printf("test: new variable\n");
		prnt_lst(g_minishell.var_lst);
		return (add2lst(&g_minishell.var_lst, g_minishell.ast->args));
	}
	printf("test: variable exists\n");
	prnt_lst(g_minishell.var_lst);
	return (1);
}
