/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:01:03 by wmarien           #+#    #+#             */
/*   Updated: 2023/11/28 12:56:03 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//handle end of file signal
void	eof_handler(void)
{
	write(1, "exit\n", 5);
	rl_clear_history();
	free_lst(&g_minishell.var_lst);
	exit(EXIT_SUCCESS);
}

//handle interuption signal whilst executing commands
void	cmd_sig_handler(int signum)
{
	if (g_minishell.sigint_child)
	{
		ft_putstr_fd("\n", 1);
		g_minishell.sigint_child = false;
		g_minishell.heredoc_sigint = true;
	}
	else if (signum == SIGINT)
	{
		g_minishell.exit_code = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

//handle signals whilst executing commands
void	handle_cmd_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, cmd_sig_handler);
}

//handle interuption signal in the command line
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

//handle signals in the command line
void	handle_global_signals(void)
{
	g_minishell.heredoc_sigint = false;
	g_minishell.sigint_child = false;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, global_sig_handler);
}
