/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:01:03 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/06 16:02:58 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	eof_handler(void)
{
	write(1, "exit\n", 5);
	rl_clear_history();
	exit (EXIT_SUCCESS);
}

void	sigint_handler(int num)
{
	(void)num;
	if (g_minishell.sigint_child)
	{
		ft_putstr_fd("\n", 1);
		g_minishell.sigint_child = false;
		g_minishell.heredoc_sigint = true;
	}
	else
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigquit_handler(int num)
{
	(void)num;
	ft_putstr_fd("Quit: 3\n", 1);
}

void	init_sighandlers(void)
{
	g_minishell.heredoc_sigint = false;
	g_minishell.sigint_child = false;
	signal (SIGINT, sigint_handler);
	signal (SIGQUIT, SIG_IGN);
}
