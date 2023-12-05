/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:10:45 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/05 12:58:10 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exittoi(char *s)
{
	int				exit_s;
	unsigned long	nmbr;

	if (!ft_isnumber(s))
	{
		exit_s = err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
		(clean_ms(), exit(exit_s));
	}
	nmbr = ft_atoi(s);
	if (ft_abs(nmbr) > LONG_MAX)
	{
		exit_s = err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
		(clean_ms(), exit(exit_s));
	}
	return (nmbr % 256);
}

int	ms_exit(char **args)
{
	int	exit_s;

	exit_s = g_minishell.exit_code;
	if (args[1])
	{
		if (args[2] && ft_isnumber(args[1]))
		{
			exit_s = err_msg((t_err){ENO_GENERAL, ERRMSG_TOO_MANY_ARGS, NULL});
			(clean_ms(), exit(exit_s));
		}
		else
			exit_s = exittoi(args[1]);
	}
	(clean_ms(), exit(exit_s));
}
