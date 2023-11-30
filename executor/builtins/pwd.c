/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:12:13 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/30 19:39:16 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//print out the current working directory
int	exec_pwd(char **args)
{
	char	cwd[PATH_MAX];

	if (args[0][3] != '\0' && args[0][3] != ' ')
		return (g_minishell.exit_code = 127, 1);
	if (args[0][3] != '\0')
		return (prnt_err("pwd: invalid usage", NULL));
	if (!getcwd(cwd, PATH_MAX))
		return (0);
	printf("%s\n", cwd);
	return (1);
}
