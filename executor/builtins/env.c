/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:11:59 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/30 19:39:14 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//print out the environment variable
int	exec_env(char **args)
{
	if (args[0][3] != '\0' && args[0][3] != ' ')
		return (g_minishell.exit_code = 127, 1);
	if (ft_strlen(g_minishell.ast->args) > 3)
		return (prnt_err("env: invalid usage", NULL));
	return (prnt_lst(g_minishell.var_lst, true), 1);
}
