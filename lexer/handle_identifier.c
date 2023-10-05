/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_identifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:12:57 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/05 20:08:51 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// fix quotes handling

int	handle_identifier(char	**line, t_token **token_lst)
{
	size_t		i;
	char		*buff;
	char		*value;
	t_token		*token;

	i = -1;
	buff = *line;
	while (buff[++i] && !is_seperator(buff + i))
		if (buff[i] == '\'' || buff[i] == '\"')
			if (!skip_quotes(buff, &i))
				return (0);
	value = ft_substr(buff, 0, i);
	if (!value)
		return (0);
	token = new_token(is_keyword(value), value);
	if (!token)
		return (lexer_err(NULL, value, NULL));
	*line += i + 1;
	return (token_add_back(token_lst, token), 1);
}
