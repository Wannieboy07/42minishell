/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:25:36 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/27 19:38:02 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//parse and populate input output doubly linked list
bool	get_io_lst(t_io_node **io_lst)
{
	t_tokentype	type;
	t_io_node	*new;

	if (g_minishell.parse_err.type)
		return (false);
	while (g_minishell.curr_token && is_redir(g_minishell.curr_token->type))
	{
		type = g_minishell.curr_token->type;
		get_next_token();
		if (!g_minishell.curr_token)
			return (set_parse_err(SYNTAX), false);
		if (g_minishell.curr_token->type != IDENTIFIER)
			return (set_parse_err(SYNTAX), false);
		new = new_io_node(type, g_minishell.curr_token->value);
		if (!new)
			return (set_parse_err(MEM), false);
		append_io_node(io_lst, new);
		get_next_token();
	}
	return (true);
}

//join arguments into a single string
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
		*args = append_args(*args, g_minishell.curr_token->value);
		if (!*args)
			return (free(to_free), false);
		free(to_free);
		get_next_token();
	}
	return (true);
}

//parse a simple command and it's arguments
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
				return (free_cmd_node(node), set_parse_err(MEM), NULL);
		}
		else if (is_redir(g_minishell.curr_token->type))
		{
			if (!get_io_lst(&(node->io_lst)))
				return (free(node->args), free(node), NULL);
		}
	}
	return (node);
}
