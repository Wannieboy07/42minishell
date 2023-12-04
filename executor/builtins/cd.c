/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 04:57:40 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/04 18:04:48 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//update environment variables based on the current working directories
static int	update_env(char *var)
{
	t_lst	*vv;
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		return (0);
	vv = check_var(g_minishell.var_lst, var);
	if (vv)
		cut_lst(&vv);
	if (!add2lst(&g_minishell.var_lst, var, cwd, true))
		return (0);
	return (1);
}

//command to change directory
int	exec_cd(char **args)
{
	if (args[1] == NULL || args[2] != NULL)
		return (prnt_arg_err("cd", NULL, "too many arguments"), 1);
	if (!update_env("OLDPWD"))
		return (0);
	if (chdir(args[1]) < 0)
		return (prnt_arg_err("cd", args[1], "invalid path"), 1);
	if (!update_env("PWD"))
		return (0);
	return (1);
}
