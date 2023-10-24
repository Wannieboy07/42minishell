/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:09:11 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/24 16:14:20 by wmarien          ###   ########.fr       */
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
	if (!ft_strlen(args))
		return (ft_strdup(str));
	if (!ft_strlen(str))
		return (ft_strdup(args));
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
	g_minishell.curr_token = g_minishell.curr_token->next;
}

bool	is_redir(t_tokentype type)
{
	if (type == GREAT || type == D_GREAT
		|| type == LESS || type == D_LESS)
		return (true);
	return (false);
}

int	get_prec(t_tokentype type)
{
	if (type == PIPE)
		return (1);
	return (0);
}

int	get_tokens_prec(void)
{
	return (get_prec(g_minishell.curr_token->type));
}
