/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:03:02 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/24 23:30:24 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*comp_path(char **paths, char *arg)
{
	char	*tmp_path;
	char	*path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		tmp_path = strjoin(paths[i], "/");
		path = strjoin(tmp_path, arg);
		if (!tmp_path || !path)
			return (NULL);
		free(tmp_path);
		printf("checking: %s\n", path);
		if (access(path, F_OK | X_OK) == VALID)
			return (path);
		free(path);
		path = NULL;
	}
	return (printf("no valid paths\n"), NULL);
}

//check the path of an external command
char	*check_path(char *arg)
{
	t_lst	*vv;
	char	**paths;

	if (!arg)
		return (NULL);
	if (arg[ft_strlen(arg) - 1] == '/')
		return (prnt_err("invalid command path", NULL), arg);
	if (access(arg, F_OK | X_OK) == VALID)
		return (printf("valid\n"), arg);
	vv = check_var(g_minishell.var_lst, "PATH");
	if (!vv)
		return (NULL);
	paths = ft_split(vv->val, ':');
	if (!paths)
		return (NULL);
	arg = comp_path(paths, arg);
	if (!arg)
		return (free_arr(paths), g_minishell.exit_code = 127, NULL);
	return (free_arr(paths), arg);
}

//execute external commands
int	exec_ext(char **args)
{
	char	*path;
	pid_t	pid;

	path = check_path(args[0]);
	if (!path)
		return (1);
	pid = fork();
	if (pid < 0)
		return (0);
	if (!pid)
		execve(path, args, g_minishell.envv);
	return (free(path), printf("success\n"), 1);
}
