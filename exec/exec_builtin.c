/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:19:06 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/05 12:56:40 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ms_echo(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (ms_cd(args[1]));
	if (ft_strcmp(args[0], "env") == 0)
		return (ms_env());
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ms_pwd());
	if (ft_strcmp(args[0], "export") == 0)
		return (ms_export(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (ms_unset(args));
	ms_exit(args);
	return (ENO_GENERAL);
}

bool	is_builtin(char *arg)
{
	if (!arg)
		return (false);
	if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "pwd") || !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset") || !ft_strcmp(arg, "env")
		|| !ft_strcmp(arg, "exit"))
		return (true);
	return (false);
}
