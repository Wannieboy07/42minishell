/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:31:37 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/27 21:54:33 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//print out the environment variable
int	exec_env(void)
{
	int	i;

	if (!g_minishell.envv)
		return (0);
	i = 0;
	while (g_minishell.envv[i])
	{
		printf("%s\n", g_minishell.envv[i]);
		i++;
	}
	return (1);
}

//print out the current working directory
int	exec_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		return (0);
	printf("%s\n", cwd);
	return (1);
}

//exit the shell in a clean way
void	exec_exit(t_token *lst)
{
	free_token_lst(&lst);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

//print out input
int	exec_echo(t_token *lst)
{
	if (!lst->next)
		return (0);
	lst = lst->next;
	if (!lst->next || ft_strncmp(lst->value, "-n", 2))
	{
		prnt_err("invalid flag for echo", NULL);
		return (0);
	}
	lst = lst->next;
	printf("%s", lst->value);
	return (1);
}

//print out the export environment variable
int	exec_export(void)
{
	t_exp_env	*exp_lst;

	if (!g_minishell.envv)
		return (0);
	exp_lst = init_exp_lst(g_minishell.envv[0]);
	if (!exp_lst)
		return (0);
	if (!add_val(exp_lst, g_minishell.envv[1]))
		return (0);
	prnt_exp_lst(exp_lst);
	return (1);
}
