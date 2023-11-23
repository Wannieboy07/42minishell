/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:12:19 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/23 20:04:28 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//error checker for echo with -n flag
static int	err_echo_n(char *args)
{
	if (args[5] == '-' && args[6] != 'n')
		return (prnt_err("echo: invalid usage", NULL));
	if (args[7] == '\0')
		return (printf("%s", ""), 1);
	if (args[7] != ' ')
		return (prnt_err("echo: invalid usage", NULL));
	return (0);
}

//initial error checker for echo
static int	err_echo(char c)
{
	if (c == '\0')
		return (printf("\n"), 1);
	if (c != ' ')
		return (g_minishell.exit_code = 127, 1);
	return (0);
}

//print out input
int	exec_echo(void)
{
	int		i;
	bool	nl;

	if (err_echo(g_minishell.ast->args[4]))
		return (1);
	nl = false;
	if (g_minishell.ast->args[5] != '-')
	{
		nl = true;
		i = 4;
	}
	else
	{
		i = 7;
		if (err_echo_n(g_minishell.ast->args))
			return (1);
	}
	while (g_minishell.ast->args[++i])
		printf("%c", g_minishell.ast->args[i]);
	if (nl)
		printf("\n");
	return (1);
}
