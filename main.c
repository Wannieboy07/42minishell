/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:25 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/25 11:52:31 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//global variable: minishell data struct
t_minishell	g_minishell;

//initialize minishell data struct variables
void	init_minishell(char **env)
{
	ft_memset(&g_minishell, 0, sizeof(t_minishell));
	g_minishell.envv = env;
	g_minishell.fdin = dup(0);
	g_minishell.fdout = dup(1);
}

//WIP
void	start_exec(void)
{
	clear_ast(&g_minishell.ast);
}

//prompt that takes inputs
int	minishell_loop(void)
{
	while (1)
	{
		g_minishell.line = readline(GREEN "» " B_CYAN "minishell$ " WHITE);
		if (!g_minishell.line)
			eof_handler(g_minishell.tokens);
		if (ft_strlen(g_minishell.line) > 0)
			add_history(g_minishell.line);
		g_minishell.tokens = lexer();
		if (!executor())
			return (prnt_err("executor", NULL));
		if (!g_minishell.tokens)
		{
			printf(GREY "info: no tokens\n" WHITE);
			continue ;
		}
		g_minishell.ast = parser();
		if (g_minishell.parse_err.type)
		{
			handle_parse_err();
			continue ;
		}
		start_exec();
	}
}

//parse inputs, execute commands, handle redirections
int	main(int ac, char **av, char **env)
{
	if (ac != 1)
		return (prnt_err("args", av));
	init_minishell(env);
	handle_global_signals();
	if (minishell_loop() == EXIT_FAILURE)
		return (EXIT_FAILURE);
}
