/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:02:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/18 19:21:24 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//tester function
static void	prnt_nxt_in_lst(t_token *lst)
{
	if (lst->next)
	{
		lst = lst->next;
		printf("test: %s\n", lst->value);
	}
}

//execute built-in commands
int	exec_builtin(t_token *lst)
{
	int	ret;

	ret = 1;
	if (!ft_strncmp(lst->value, "echo", 4))
		;
	else if (!ft_strncmp(lst->value, "cd", 2))
		;
	else if (!ft_strncmp(lst->value, "pwd", 3))
		ret = exec_pwd();
	else if (!ft_strncmp(lst->value, "export", 6))
		;
	else if (!ft_strncmp(lst->value, "unset", 5))
		;
	else if (!ft_strncmp(lst->value, "env", 3))
		exec_env();
	else if (!ft_strncmp(lst->value, "exit", 4))
		exec_exit(lst);
	else
		return (1);
	if (ret == 0)
		return (0);
	prnt_nxt_in_lst(lst);
	return (1);
}

//execute commands if any are found
int	exec_cmd(void)
{
	t_token	*lst;

	lst = g_minishell.tokens;
	if (!lst)
	{
		printf(GREY "info: nothing to execute\n" WHITE);
		return (1);
	}
	print_lst(lst);
	while (lst)
	{
		if (!exec_builtin(lst))
			return (0);
		lst = lst->next;
	}
	return (1);
}

//parse linked list and execute commands
int	executor(void)
{
	if (!exec_cmd())
		return (0);
	return (1);
}
