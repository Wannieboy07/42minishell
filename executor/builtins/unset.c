/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:20:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/16 16:59:38 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//removes variables
int	rm_var(char *var, t_lst *lst)
{
	if (!lst)
		return (1);
	while (lst)
	{
		if (!ft_strncmp(lst->val, var, ft_strlen(var)))
			return (cut_lst(lst), 1);
		lst = lst->next;
	}
	return (1);
}

//check whether a variable exists within the environment
int	check_var(char *var, t_lst *lst)
{
	if (!var || !lst)
		return (0);
	while (lst)
	{
		if (!ft_strncmp(lst->val, var, ft_strlen(var)))
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
		return (g_minishell.exit_code = 127, 1);
	if (g_minishell.ast->args[5] == '\0' || g_minishell.ast->args[5] != ' '
		|| g_minishell.ast->args[6] == '-')
		return (prnt_err("unset: invalid usage", NULL));
	args = ft_strdup(g_minishell.ast->args + 6);
	if (!args)
		return (0);
	if (!check_var(args, g_minishell.exp_env))
		return (1);
	rm_var(args, g_minishell.exp_env);
	free(args);
	return (1);
}
