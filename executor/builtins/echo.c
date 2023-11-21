/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:12:19 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/21 17:54:34 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//print out input
int	exec_echo(void)
{
	int		i;
	bool	nl;

	if (g_minishell.ast->args[4] == '\0' && g_minishell.ast->args[4] != ' ')
		return (g_minishell.exit_code = 127,
			prnt_err("echo: invalid usage", NULL));
	nl = false;
	if (g_minishell.ast->args[5] != '-')
	{
		nl = true;
		i = 4;
	}
	else
		i = 7;
	if (g_minishell.ast->args[5] == '-' && g_minishell.ast->args[6] != 'n')
		prnt_err("echo: invalid usage", NULL);
	while (g_minishell.ast->args[++i])
		printf("%c", g_minishell.ast->args[i]);
	if (nl)
		printf("\n");
	return (1);
}
