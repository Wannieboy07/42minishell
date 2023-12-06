/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:06:18 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/06 14:45:25 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

void	init_minishell(char **env)
{
	ft_memset(&g_minishell, 0, sizeof(t_minishell));
	g_minishell.envv = env;
	init_envlst();
	g_minishell.fdin = dup(0);
	g_minishell.fdout = dup(1);
}

void	clean_ms(void)
{
	garbage_collector(NULL, true);
	clear_ast(&g_minishell.ast);
	clear_envlst();
	rl_clear_history();
}

void	start_exec(void)
{
	signal(SIGQUIT, sigquit_handler);
	init_tree(g_minishell.ast);
	if (g_minishell.heredoc_sigint)
	{
		clear_ast(&g_minishell.ast);
		g_minishell.heredoc_sigint = false;
	}
	g_minishell.exit_code = exec_node(g_minishell.ast, false);
	clear_ast(&g_minishell.ast);
}

int	minishell_loop(void)
{
	while (1)
	{
		init_sighandlers();
		g_minishell.line = readline(GREEN "» " B_CYAN "minishell$ " WHITE);
		if (!g_minishell.line)
			(clean_ms(), eof_handler());
		if (ft_strlen(g_minishell.line) > 0)
			add_history(g_minishell.line);
		g_minishell.tokens = lexer();
		if (!g_minishell.tokens)
			continue ;
		g_minishell.ast = parser();
		if (g_minishell.parse_err.type)
		{
			handle_parse_err();
			continue ;
		}
		start_exec();
	}
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
		return (prnt_err("run ./minishell without arguments"));
	init_minishell(env);
	if (minishell_loop() == EXIT_FAILURE)
		return (EXIT_FAILURE);
}
