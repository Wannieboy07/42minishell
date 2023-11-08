/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:12:13 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/08 03:08:44 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//print out the current working directory
int	exec_pwd(void)
{
	char	cwd[PATH_MAX];

	if (g_minishell.ast->args[3] != '\0' && g_minishell.ast->args[3] != ' ')
		return (prnt_err("command not found", NULL));
	if (g_minishell.ast->args[3] != '\0')
		return (prnt_err("pwd: invalid usage", NULL));
	if (!getcwd(cwd, PATH_MAX))
		return (0);
	printf("%s\n", cwd);
	return (1);
}
