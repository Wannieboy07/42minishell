/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:29:56 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/05 23:40:31 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer(char *line)
{
	int		err;
	t_token	*token_lst;
	t_token	*curr;

	err = 0;
	token_lst = NULL;
	while (*line)
	{
		if (err)
			return (lexer_err(&token_lst, NULL, "lexer failed"));
		while (*line && ft_isspace(*line))
			(*line)++;
		if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1))
			err = !handle_seperator(&line, &token_lst);
		else
			err = !handle_identifier(&line, &token_lst);
	}
	curr = token_lst;
	while (curr)
	{
		printf("Type: %d\nValue: %s\n", curr->type, curr->value);
		curr = curr->next;
	}
	return (0);
}
