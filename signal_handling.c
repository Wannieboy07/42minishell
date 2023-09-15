#include "minishell.h"

static void	cmd_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
//		set error code 130
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

static void	global_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
//		set error code 1
		write(1,"\n", 1);
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
