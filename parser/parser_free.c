/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:11:10 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/19 17:12:30 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_io_lst(t_io_node **head)
{
	t_io_node	*curr;
	t_io_node	*next;

	curr = *head;
	if (!curr)
		return ;
	while (curr)
	{
		free(curr->value);
		free_arr(curr->exp_value);
		next = curr->next;
		free(curr);
		curr = next;
	}
	*head = NULL;
}

void	free_cmd_node(t_node *node)
{
	if (!node)
		return ;
	free_io_lst(&(node->io_lst));
	free(node->args);
	free_arr(node->exp_args);
}

void	free_ast_nodes(t_node *node)
{
	if (!node)
		return ;
	if (node->type == P_CMD)
		free_cmd_node(node);
	else
	{
		if (node->left)
			free_ast_nodes(node->left);
		if (node->right)
			free_ast_nodes(node->right);
	}
	free(node);
}

void	clear_ast(t_node **ast)
{
	free_ast_nodes(*ast);
	*ast = NULL;
	free_token_lst(&g_minishell.tokens);
}
