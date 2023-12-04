/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:25 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/04 17:51:39 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//global variable: minishell data struct
t_minishell	g_minishell;

//initialize minishell data struct variables
static int	init_minishell(char **env)
{
	ft_memset(&g_minishell, 0, sizeof(t_minishell));
	g_minishell.envv = env;
	g_minishell.fdin = dup(0);
	g_minishell.fdout = dup(1);
	if (g_minishell.fdin < 0 || g_minishell.fdout < 0)
		return (0);
	if (!init_var_lst())
		return (0);
	return (1);
}

//cleanup handler
void	clean_ms(void)
{
	garbage_collector(NULL, true);
	clear_ast(&g_minishell.ast);
	clear_envlst();
	rl_clear_history();
}

//set up for execution and execute
static int	start_exec(void)
{
	handle_cmd_signals();
	init_tree(g_minishell.ast);
	prnt_ast(g_minishell.ast);
	if (!executor())
		return (0);
	clear_ast(&g_minishell.ast);
	return (1);
}

//prompt that takes inputs and handles them
int	minishell_loop(void)
{
	while (1)
	{
		handle_global_signals();
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
		if (!start_exec())
			break ;
	}
	return (clear_ast(&g_minishell.ast), 0);
}

//parse inputs, execute commands, handle redirections
int	main(int ac, char **av, char **env)
{
	if (ac != 1)
		return (prnt_err("args", av));
	if (!init_minishell(env))
		return (EXIT_FAILURE);
	if (!minishell_loop())
		return (EXIT_FAILURE);
}
