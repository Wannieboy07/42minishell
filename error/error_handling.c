#include "../minishell.h"

int	prnt_err(char *str)
{
	ft_putendl_fd(str, 1);
	return (1);
}

int	lexer_err(t_token **token_lst, char *str, char *err_str)
{
	if (*token_lst)
		free_token_lst(token_lst);
	if (str)
		free(str);
	if (err_str)
		prnt_err(err_str);
	return (1);
}
