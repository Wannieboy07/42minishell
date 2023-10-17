/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_identifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:12:57 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/17 14:34:00 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//parse input, identify token and store data
int	handle_identifier(char	**line, t_token **token_lst)
{
	size_t		i;
	char		*buff;
	char		*value;
	t_token		*token;

	i = 0;
	buff = *line;
	while (buff[i] && !is_seperator(buff + i))
	{
		if (buff[i] == S_QUOTES || buff[i] == D_QUOTES)
		{
			if (!skip_quotes(buff, &i))
				return (prnt_quote_err(), 0);
		}
		else
			i++;
	}
	value = ft_substr(buff, 0, i);
	if (!value)
		return (0);
	token = new_token(IDENTIFIER, value);
	if (!token)
		return (free(value), 0);
	*line += i;
	return (token_add_back(token_lst, token), 1);
}
