#include "minishell.h"

int	exit_process(char *line)
{
	if (line)
		free(line);
	return (1);
}

int	minishell_loop()
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

int	main(int ac, char **av, char **envp)
{
//	t_main	data;

	(void)av;
	(void)envp;
	if (ac != 1)
		return (prnt_err("run ./minishell without arguments"));
	handle_global_signals();
//	init_envv(envp);
//	init_data(data);
	if (minishell_loop() == EXIT_FAILURE)
		return (EXIT_FAILURE);
}
