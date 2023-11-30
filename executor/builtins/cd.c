/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 04:57:40 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/30 19:39:12 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//command to change directory
int	exec_cd(char **args)
{
	char	*path;
	t_lst	*vv;
	char	cwd[PATH_MAX];

	if (args[0][2] == '\0')
		return (prnt_err("cd: invalid usage", NULL), 1);
	if (args[0][2] != ' ')
		return (g_minishell.exit_code = 127, 1);
	path = ft_strdup(g_minishell.ast->args + 3);
	if (!path)
		return (0);
	if (ft_strchr(path, ' '))
		return (free(path), prnt_err("cd: too many paths specified", NULL), 1);
	if (!getcwd(cwd, PATH_MAX))
		return (free(path), 0);
	if (chdir(path) < 0)
		return (free(path), prnt_err("cd: invalid path", NULL), 1);
	vv = check_var(g_minishell.var_lst, "OLDPWD");
	if (!vv)
		return (free(path), 1);
	cut_lst(&vv);
	if (!add2lst(&g_minishell.var_lst, "OLDPWD", cwd, true))
		return (free(path), 0);
	return (free(path), 1);
}
