#include "../minishell.h"

int	handle_identifier(char	**line, t_token **token_lst)
{
	int	i;
	char	*buff;
	char	*value;
	t_token	*token;

	i = 0;
	buff = *line;
	while (buff[i] && !is_seperator(*buff + i))
	{
		if (buff[i] == '\'' || buff[i] == '\"')
		{
			while (buff[++i] && (buff[i] != '\'' || buff[i] != '\"'))
				if (!buff[i + 1])
					return (0);
		}
		else
			i++;

	}
	value = ft_substr(buff, 0, i);
	if (!value)
		return (1);
	if (is_keyword(value))
		token = new_token(KEYWORD,value);
	else
		token = new_token(IDENTIFIER, value);
	if (!token)
		return (lexer_err(NULL, value, NULL));
	*line += i;
	return (token_add_back(token_lst, token), 1);
}
