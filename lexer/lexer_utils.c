/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:31:57 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/10 00:07:42 by lpeeters         ###   ########.fr       */
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

//check if character is any sort seperator
bool	is_seperator(char *c)
{
	if (*c == ' ' || *c == '\t' || *c == '|'
		|| *c == '<' || *c == '>')
		return (true);
	return (false);
}

//check if character is any sort keyword
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

//print an error specific to unclosed quotation marks
void	prnt_quote_err(void)
{
	ft_putendl_fd(RED "» " D_BLUE "minishell: " WHITE "unclosed quote", 2);
	g_minishell.exit_code = 258;
}
