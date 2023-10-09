/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:39:19 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/09 17:39:21 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

void	init_minishell(char **env)
{
	ft_memset(&g_minishell, 0, sizeof(t_minishell));
	g_minishell.envv = env;
	g_minishell.fdin = dup(0);
	g_minishell.fdout = dup(1);
}

int	minishell_loop(void)
{
	while (1)
	{
		g_minishell.line = readline("\033[92m»\033[1;36m minishell$\033[0;97m ");
		if (!g_minishell.line)
			eof_handler();
		if (ft_strlen(g_minishell.line) > 0)
			add_history(g_minishell.line);
		g_minishell.tokens = lexer();
		if (!g_minishell.tokens)
			continue ;
	}
}

//	init_envv(envp);

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
		return (prnt_err("run ./minishell without arguments"));
	init_minishell(env);
	handle_global_signals();
	if (minishell_loop() == EXIT_FAILURE)
		return (EXIT_FAILURE);
}
