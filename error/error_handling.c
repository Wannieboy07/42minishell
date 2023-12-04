/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:04 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/04 17:43:06 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//print argument errors
int	prnt_arg_err(char *type, char *arg, char *msg)
{
	if (!type && !arg && !msg)
		return (g_minishell.exit_code = 1, 1);
	ft_putstr_fd(RED "Error" GREY ": ", 2);
	if (type)
	{
		ft_putstr_fd(type, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd("'", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("'", 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (g_minishell.exit_code = 1, 1);
}

//print errors
int	prnt_err(char *str, char **av)
{
	int	i;

	ft_putstr_fd(RED "Error" GREY ": ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	if (str && av)
		ft_putstr_fd(": ", 2);
	if (av)
	{
		ft_putstr_fd("run ", 2);
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd(" without arguments\n", 2);
		ft_putstr_fd("Tip: change ", 2);
		i = 0;
		while (av[i + 1])
		{
			ft_putstr_fd(av[i++], 2);
			ft_putstr_fd(" ", 2);
		}
		ft_putstr_fd(av[i], 2);
		ft_putstr_fd(" to ", 2);
		ft_putstr_fd(av[0], 2);
	}
	ft_putstr_fd("\n", 2);
	return (1);
}
