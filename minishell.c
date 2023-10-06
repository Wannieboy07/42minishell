/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:25 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/06 19:10:05 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//global variable: minishell data struct
t_minishell	g_minishell;

	//init_envv()

//initialize minishell data struct variables
void	init_minishell(char **env)
{
	ft_memset(&g_minishell, 0, sizeof(t_minishell));
	g_minishell.envv = env;
	g_minishell.fdin = dup(0);
	g_minishell.fdout = dup(1);
}

//prompt that takes inputs
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

//	t_main	data;

//	init_envv(envp);
//	init_data(data);

//parse inputs, execute commands, handle redirections
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
