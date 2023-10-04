/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:15 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/04 16:20:17 by lpeeters         ###   ########.fr       */
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
		if (is_seperator(*line))
			err = !handle_seperator(&line, &token_lst);
		else
			err = !handle_identifier(&line, &token_lst);
	}
	return (0);
}
