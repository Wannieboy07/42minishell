/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 04:57:40 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/07 20:20:39 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//command to change directory
int	exec_cd(void)
{
	char	*path;

	if (g_minishell.ast->args[2] == '\0')
		return (prnt_err("cd: invalid usage", NULL), 1);
	if (g_minishell.ast->args[2] != ' ')
		return (prnt_err("command not found", NULL));
	path = ft_strdup(g_minishell.ast->args + 3);
	if (!path)
		return (0);
	if (chdir(path) < 0)
		return (prnt_err("cd: invalid path", NULL));
	return (1);
}
