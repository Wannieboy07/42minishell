/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:31:37 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/18 19:14:54 by lpeeters         ###   ########.fr       */
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
