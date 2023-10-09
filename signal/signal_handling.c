/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:22 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/09 17:41:26 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	eof_handler(void)
{
	write(1, "exit\n", 5);
	rl_clear_history();
	exit (1);
}

void	cmd_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_minishell.exit_code = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	global_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_minishell.exit_code = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_cmd_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, cmd_sig_handler);
}

void	handle_global_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, global_sig_handler);
}
