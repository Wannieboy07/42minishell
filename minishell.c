/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:25 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/04 23:49:27 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle memory
int	exit_process(char *line)
{
	if (line)
		free(line);
	return (1);
}

//prompt that takes inputs
int	minishell_loop(void)
{
	char	*line;

	while (1)
	{
		line = readline("<minishell> ");
		if (!line)
			eof_handler();
		if (ft_strlen(line) > 0)
			add_history(line);
		if (lexer(line) == EXIT_FAILURE)
			return (exit_process(line));
	}
}

//	t_main	data;

//	init_envv(envp);
//	init_data(data);

//parse inputs, execute commands, handle redirections
int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)envp;
	if (ac != 1)
		return (prnt_err("run ./minishell without arguments"));
	handle_global_signals();
	if (minishell_loop() == EXIT_FAILURE)
		return (EXIT_FAILURE);
}
