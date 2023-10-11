/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:29:56 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/11 12:17:55 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*lexer(void)
{
	int		err;
	char	*line;
	t_token	*token_lst;
	t_token	*curr;

	err = 0;
	line = g_minishell.line;
	token_lst = NULL;
	while (*line)
	{
		if (err)
			return (free_token_lst(&token_lst), NULL);
		if (ft_isspace(*line))
			skip_spaces(&line);
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
	line = g_minishell.line;
	free(line);
	g_minishell.line = NULL;
	return (token_lst);
}
