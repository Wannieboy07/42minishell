/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:09:11 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/18 15:53:20 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_args(char *args, char *str)
{
	char	*new;
	size_t	length;
	size_t	i;
	size_t	j;

	if (!args || !str)
		return (NULL);
	length = ft_strlen(args) + ft_strlen(str) + 2;
	new = malloc(sizeof(char) * length);
	if (!new)
		return (NULL);
	i = -1;
	while (args[++i])
		new[i] = args[i];
	new[i++] = ' ';
	j = 0;
	while (str[j])
		new[i++] = str[j++];
	new[i] = '\0';
	return (new);
}

void	get_next_token(void)
{
	g_minishell.curr_token = g_minishell.curr_token -> next;
}

bool	is_redir(t_token_type type)
{
	if (type == T_LESS || type == T_GREAT
		|| type == T_DLESS || type == T_DGREAT)
		return (true);
	return (false);
}

int	get_prec(t_token_type type)
{
	if (type == PIPE)
		return (1);
	return (0);
}

int	get_tokens_prec(void)
{
	return (ft_prec(g_minishell.curr_token->type));
}
