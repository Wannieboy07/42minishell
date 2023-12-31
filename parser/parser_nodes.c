/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:51:54 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/20 00:52:34 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//determine input/output type
t_iotype	get_iotype(t_tokentype type)
{
	if (type == GREAT)
		return (OUT);
	if (type == D_GREAT)
		return (APPEND);
	if (type == LESS)
		return (IN);
	return (HERDOC);
}

//create a new entree to an abstract syntax tree doubly linked list
t_node	*new_node(t_nodetype type)
{
	t_node	*new;

	new = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	new->type = type;
	return (new);
}

//create a new entree to an input/output doubly linked list
t_io_node	*new_io_node(t_tokentype type, char *value)
{
	t_io_node	*new;

	new = (t_io_node *)ft_calloc(1, sizeof(t_io_node));
	if (!new)
		return (NULL);
	new->type = get_iotype(type);
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new), NULL);
	return (new);
}

//add an entree to an input/output doubly linked list
void	append_io_node(t_io_node **head, t_io_node *io_node)
{
	t_io_node	*curr;

	if (!*head)
	{
		*head = io_node;
		return ;
	}
	curr = *head;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = io_node;
}
