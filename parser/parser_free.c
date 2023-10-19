/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:11:10 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/20 00:54:49 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//free the memory of an input/output doubly linked list
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

//free all the memory associated with a command's data
void	free_cmd_node(t_node *node)
{
	if (!node)
		return ;
	free_io_lst(&(node->io_lst));
	free(node->args);
	free_arr(node->exp_args);
}

//free the memory of an abstract syntax tree doubly linked list
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

//free all the memory associated with an abstract syntax tree
void	clear_ast(t_node **ast)
{
	free_ast_nodes(*ast);
	*ast = NULL;
	free_token_lst(&g_minishell.tokens);
}
