/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:11:59 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/04 18:04:24 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//print out the environment variable
int	exec_env(char **args)
{
	if (args[1] != NULL)
		return (prnt_arg_err("env", NULL, "too many arguments"));
	return (prnt_lst(g_minishell.var_lst, true), 1);
}
