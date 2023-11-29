/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:37:56 by wmarien           #+#    #+#             */
/*   Updated: 2023/11/29 10:45:55 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*combine_atoms(t_node *left, t_node *right)
{
	t_node	*node;

	if (g_minishell.parse_err.type)
		return (NULL);
	node = new_node(P_PIPE);
	if (!node)
		return (set_parse_err(MEM), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*parse_atom(void)
{
	if (g_minishell.parse_err.type)
		return (NULL);
	if (g_minishell.curr_token->type == PIPE)
		return (set_parse_err(SYNTAX), NULL);
	else
		return (get_simple_cmd());
}

t_node	*parse_expr(int min_prec)
{
	t_node		*left;
	t_node		*right;
	t_tokentype	op;

	if (g_minishell.parse_err.type || !g_minishell.curr_token)
		return (NULL);
	left = parse_atom();
	if (!left)
		return (NULL);
	while (g_minishell.curr_token && g_minishell.curr_token->type == PIPE
		&& get_tokens_prec() >= min_prec)
	{
		op = g_minishell.curr_token->type;
		get_next_token();
		if (!g_minishell.curr_token)
			return (set_parse_err(SYNTAX), left);
		right = parse_expr(get_prec(op) + 1);
		if (!right)
			return (left);
		left = combine_atoms(left, right);
		if (!left)
			return (clear_ast(&left), clear_ast(&right), NULL);
	}
	return (left);
}

t_node	*parser(void)
{
	t_node	*ast;

	g_minishell.curr_token = g_minishell.tokens;
	ast = parse_expr(0);
	if (g_minishell.curr_token)
		return (set_parse_err(SYNTAX), ast);
	return (ast);
}
