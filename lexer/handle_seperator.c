/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_seperator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:12 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/04 16:20:20 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_seperator(t_tokentype type, char **line, t_token **token_lst)
{
	t_token	*token;

	token = new_token(type, NULL);
	if (!token)
		return (1);
	(*line)++;
	if (type == D_GREAT || type == D_LESS)
		(*line)++;
	return (token_add_back(token_lst, token), 1);
}

int	handle_seperator(char **line, t_token **token_lst)
{
	if (!ft_strncmp(*line, ">>", 2))
		return (add_seperator(GREAT, line, token_lst));
	else if (!ft_strncmp(*line, ">", 1))
		return (add_seperator(D_GREAT, line, token_lst));
	else if (!ft_strncmp(*line, "<<", 2))
		return (add_seperator(LESS, line, token_lst));
	else if (!ft_strncmp(*line, "<", 1))
		return (add_seperator(D_LESS, line, token_lst));
	else
		return (add_seperator(PIPE, line, token_lst));
}
