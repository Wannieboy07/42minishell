/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:12:19 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/06 23:37:29 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//print out input
int	exec_echo(void)
{
	int	i;

	if (g_minishell.ast->args[4] == '\0')
		prnt_err("echo: invalid usage\nInfo: example: echo -n <arg(s)>", NULL);
	else if (g_minishell.ast->args[4] != ' ')
		return (1);
	else if (ft_strncmp(g_minishell.ast->args, "echo -n ", 8))
		prnt_err("echo: invalid usage\nInfo: example: echo -n <arg(s)>", NULL);
	else
	{
		i = 7;
		while (g_minishell.ast->args[++i])
			printf("%c", g_minishell.ast->args[i]);
	}
	return (1);
}
