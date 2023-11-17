/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:22 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/17 21:15:27 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//handle end of of file signal
void	eof_handler(void)
{
	write(1, "exit\n", 5);
	free_lst(g_minishell.exp_env);
	free_lst(g_minishell.var_lst);
	rl_clear_history();
	exit (EXIT_SUCCESS);
}

//handle interuption signal whilst executing commands
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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, global_sig_handler);
}
