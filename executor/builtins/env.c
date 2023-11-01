/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:11:59 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/01 02:17:24 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//print out the environment variable
int	exec_env(void)
{
	int	i;

	if (ft_strlen(g_minishell.ast->args) > 3)
		return (prnt_err("env: invalid usage", NULL));
	i = -1;
	while (g_minishell.envv[++i])
		printf("%s\n", g_minishell.envv[i]);
	return (1);
}
