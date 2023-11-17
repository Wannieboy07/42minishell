/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:20:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/17 20:20:39 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//removes variables
int	rm_var(char *var, t_lst *lst)
{
	if (!var || !lst)
		return (1);
	while (lst)
	{
		if (ft_strlen(var) == ft_strlen(lst->val)
			&& !ft_strncmp(var, lst->val, ft_strlen(var)))
			return (cut_lst(lst), 1);
		lst = lst->next;
	}
	return (1);
}

//check whether a variable exists within the environment
int	check_var(char **var, t_lst *lst)
{
	if (!*var || !lst)
		return (0);
	if (!ft_strchr(*var, '='))
	{
		if (!var_val(var, g_minishell.var_lst))
			return (0);
		if (!*var)
			return (1);
		if (!complete_var(var))
			return (0);
		if (!*var)
			return (1);
	}
	while (lst)
	{
		if (ft_strlen(*var) == ft_strlen(lst->val)
			&& !ft_strncmp(*var, lst->val, ft_strlen(*var)))
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
	args = g_minishell.ast->args + 6;
	if (check_var(&args, g_minishell.var_lst))
		rm_var(args, g_minishell.var_lst);
	if (check_var(&args, g_minishell.exp_env))
		rm_var(args, g_minishell.exp_env);
	return (1);
}
