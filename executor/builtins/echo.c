/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:12:19 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/04 17:56:19 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//error checker for echo with -n flag
static int	err_echo_flag(char **args)
{
	char	*flag;

	flag = args[1];
	if (flag[1] != 'n' || flag[2] != '\0')
	{
		if (flag[2] == '\0')
			return (prnt_arg_err("echo", args[1], "invalid option"));
		return (prnt_arg_err("echo", args[1], "invalid options"));
	}
	if (args[2] == NULL)
		return (printf("%s", ""), 1);
	return (0);
}

//print out input
int	exec_echo(char **args)
{
	bool	nl;
	int		i;

	if (args[1] == NULL)
		return (printf("\n"), 1);
	nl = true;
	i = 0;
	if (args[1][0] == '-')
	{
		if (err_echo_flag(args))
			return (1);
		nl = false;
		i = 1;
	}
	while (args[++i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (1);
}
