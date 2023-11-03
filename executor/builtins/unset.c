/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:20:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/03 23:38:07 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//WIP
//check whether a variable exists wihtin the environment
int	check_var(char *var)
{
	t_exp_env	*lst;

	if (!var)
		return (1);
	lst = g_minishell.exp_env;
	if (!lst)
		return (1);
	while (lst)
	{
		if (!ft_strncmp(lst->var, var, ft_strlen(lst->var)))
			return (1);
		lst = lst->next;
	}
	printf("variable does not exist\n");
	return (0);
}

//WIP
//Variables yet to be impemented.
//command to remove exported variables
int	exec_unset(void)
{
	if (g_minishell.ast->args[6] == '\0')
		return (prnt_err("unset: invalid usage", NULL));
	if (!check_var(ft_strdup(g_minishell.ast->args + 6)))
		return (1);
	printf("variable exists\n");
	return (1);
}
