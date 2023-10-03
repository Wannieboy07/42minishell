#include "../minishell.h"

bool	is_seperator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_keyword(char *value)
{
	if (!ft_strncmp(value, "echo", 4) || !ft_strncmp(value, "cd", 2) || !ft_strncmp(value, "pwd", 3) ||
			!ft_strncmp(value, "export", 6) || !ft_strncmp(value, "unset", 5) ||
			!ft_strncmp(value, "env", 3) || !ft_strncmp(value, "exit", 4))
		return (true);
	else
		return (false);
}
