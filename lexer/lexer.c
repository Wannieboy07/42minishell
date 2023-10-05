/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:29:56 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/05 20:16:45 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer(char *line)
{
	int			err;
	t_token		*token_lst;

	err = 0;
	token_lst = NULL;
	while (*line)
	{
		if (err)
			return (lexer_err(&token_lst, NULL,
					"\033[0;31mlexer failed\033[0;39m"));
		while (ft_isspace(*line))
			(*line)++;
		if (is_seperator(line))
			err = !handle_seperator(&line, &token_lst);
		else
			err = !handle_identifier(&line, &token_lst);
	}
	return (0);
}
