/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:31:57 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/06 00:03:35 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	skip_quotes(char *buff, size_t *i)
{
	char	quote;

	quote = buff[*i];
	while (buff[++(*i)] && buff[*i] != quote)
		if (!buff[*i + 1])
			return (false);
	(*i)++;
	return (true);
}

bool	is_seperator(char *c)
{
	if (*c == ' ' || *c == '\t' || *c == '|'
		|| *c == '<' || *c == '>')
		return (true);
	return (false);
}

t_tokentype	is_keyword(char *value)
{
	if (!ft_strncmp(value, "echo", 4) || !ft_strncmp(value, "cd", 2)
		|| !ft_strncmp(value, "pwd", 3) || !ft_strncmp(value, "export", 6)
		|| !ft_strncmp(value, "unset", 5) || !ft_strncmp(value, "env", 3)
		|| !ft_strncmp(value, "exit", 4))
		return (KEYWORD);
	else
		return (IDENTIFIER);
}
