/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:25:36 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/18 15:08:39 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	git_io_lst(t_io_node **io_lst)

bool	join_args(char	**args)
{
	char	*to_free;

	if (g_minishell.parse_err.type)
		return (false);
	if (!*args)
		*args = ft_strdup("");
	if (!*args)
		return (false);
	while (g_minishell.curr_token
		&& g_minishell.curr_token->type == IDENTIFIER)
	{
		to_free = *args;
		*args = append_arg(*args, g_minishell.curr_token->value);
		if (!*args)
			return (free(to_free), false);
		free(to_free);
		get_next_token();
	}
	return (true);
}

t_node	*get_simple_cmd(void)
{
	t_node	*node;

	if (g_minishell.parse_err.type)
		return (NULL);
	node = new_node(P_CMD);
	if (!node)
		return (set_parse_err(MEM), NULL);
	while (g_minishell.curr_token
		&& (g_minishell.curr_token->type == IDENTIFIER
		|| is_redir(g_minishell.curr_token->type)))
	{
		if (g_minishell.curr_token->type == IDENTIFIER)
		{
			if (!join_args(&(node->args)))
				return (clear_cmd_node(node), set_parse_err(MEM), NULL);
		}
		else if (is_redir(g_minishell.curr_token->type))
		{
			if (get_io_lst(&(node->io_lst)))
				return (free(node->args), free(node), NULL);
		}
	}
	return (node);
}
