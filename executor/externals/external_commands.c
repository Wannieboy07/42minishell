/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:03:02 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/28 15:31:14 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*comp_path(char **paths, char *arg, struct stat fstat)
{
	char	*tmp_path;
	char	*path;
	int		i;

	if (!paths || !arg)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		tmp_path = strjoin(paths[i], "/");
		if (!tmp_path)
			return (NULL);
		path = strjoin(tmp_path, arg);
		free(tmp_path);
		if (!path)
			return (NULL);
		if (stat(path, &fstat) == VALID
			&& S_ISREG(fstat.st_mode) && (fstat.st_mode & S_IXUSR))
			return (path);
		free(path);
		path = NULL;
	}
	return (NULL);
}

//check the path of an external command
char	*check_path(char *arg)
{
	t_lst		*vv;
	char		*path;
	char		**paths;
	struct stat	fstat;

	if (!arg)
		return (NULL);
	if (arg[ft_strlen(arg) - 1] == '/')
		return (prnt_err("invalid command path", NULL), NULL);
	if (stat(arg, &fstat) == VALID
		&& S_ISREG(fstat.st_mode) && (fstat.st_mode & S_IXUSR))
		return (ft_strdup(arg));
	vv = check_var(g_minishell.var_lst, "PATH");
	if (!vv)
		return (NULL);
	paths = ft_split(vv->val, ':');
	if (!paths)
		return (NULL);
	path = comp_path(paths, arg, fstat);
	if (!path)
		return (free_arr(paths), NULL);
	return (free_arr(paths), path);
}

//execute external commands
int	exec_ext(char **args)
{
	char	*path;

	if (!args)
		return (1);
	path = check_path(args[0]);
	if (!path)
		return (1);
	if (execve(path, args, g_minishell.envv) < 0)
		return (0);
	return (g_minishell.exit_code = 0, free(path), 1);
}
