/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:02:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/13 23:30:54 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//execute built-in commands
int	exec_builtin(t_token *lst)
{
	if (!ft_strncmp(lst->value, "echo", 4))
		;
	else if (!ft_strncmp(lst->value, "cd", 2))
		;
	else if (!ft_strncmp(lst->value, "pwd", 3))
		;
	else if (!ft_strncmp(lst->value, "export", 6))
		;
	else if (!ft_strncmp(lst->value, "unset", 5))
		;
	else if (!ft_strncmp(lst->value, "env", 3))
		;
	else if (!ft_strncmp(lst->value, "exit", 4))
		eof_handler();
	else
		return (0);
	if (lst->next)
	{
		lst = lst->next;
		printf("\ntest: %s\n", lst->value);
	}
	return (1);
}

//execute commands if any are found
int	exec_cmd(void)
{
	t_token	*lst;
	bool	has_cmd;

	lst = g_minishell.tokens;
	if (!lst)
	{
		printf(GREY "info: nothing to execute\n" WHITE);
		return (1);
	}
	has_cmd = false;
	while (lst)
	{
		if (lst->type == 2)
		{
			has_cmd = true;
			if (!exec_builtin(lst))
				return (0);
		}
		else if (lst->type == 0)
			printf(GREY "info: not yet implemented\n" WHITE);
		lst = lst->next;
	}
	if (has_cmd == false)
		printf(GREY "info: nothing to execute\n" WHITE);
	return (1);
}

//parse linked list and execute commands
int	executor(void)
{
	if (!exec_cmd())
		return (0);
	return (1);
}
