/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:20:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/08 01:22:38 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//removes variables
int	rm_var(char *var)
{
	t_lst	*lst;

	if (!g_minishell.exp_env)
		return (1);
	lst = g_minishell.exp_env;
	while (lst)
	{
		if (!ft_strncmp(lst->val, var, ft_strlen(lst->val)))
			return (cut_lst(lst), 1);
		lst = lst->next;
	}
	return (1);
}

//check whether a variable exists wihtin the environment
int	check_var(char *var)
{
	t_lst	*lst;

	if (!var)
		return (0);
	lst = g_minishell.exp_env;
	if (!lst)
		return (0);
	while (lst)
	{
		if (!ft_strncmp(lst->val, var, ft_strlen(lst->val)))
			return (1);
		lst = lst->next;
	}
	return (0);
}

//Shell variables yet to be impemented.
//command to remove variables
int	exec_unset(void)
{
	char	*args;

	if (g_minishell.ast->args[5] != '\0' && g_minishell.ast->args[5] != ' ')
		return (prnt_err("command not found", NULL));
	if (g_minishell.ast->args[5] == '\0' || g_minishell.ast->args[5] != ' '
		|| g_minishell.ast->args[6] == '-')
		return (prnt_err("unset: invalid usage", NULL));
	args = ft_strdup(g_minishell.ast->args + 6);
	if (!args)
		return (0);
	if (!check_var(args))
		return (1);
	if (!rm_var(args))
		return (0);
	free(args);
	return (1);
}
