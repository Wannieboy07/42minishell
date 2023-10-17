/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:31:57 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/17 19:55:29 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//parse buffer till the next quote, skipping other quote type
bool	skip_quotes(char *buff, size_t *i)
{
	char	quote;

	quote = buff[(*i)++];
	if (ft_strchr(buff + *i, quote))
	{
		while (buff[*i] != quote)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}

//skip over any amount of spaces that were found
void	skip_spaces(char **line)
{
	while (**line && ft_isspace(**line))
		(*line)++;
}

//check if character is any sort seperator
bool	is_seperator(char *c)
{
	if (*c == ' ' || *c == '\t' || *c == '|'
		|| *c == '<' || *c == '>')
		return (true);
	return (false);
}

//print an error specific to unclosed quotation marks
void	prnt_quote_err(void)
{
	ft_putendl_fd(RED "» " CYAN "minishell: " WHITE "unclosed quote", 2);
	g_minishell.exit_code = 258;
}
