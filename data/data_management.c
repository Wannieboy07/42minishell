/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:06:30 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/20 23:53:35 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//printing of a doubly linked list
void	prnt_lst(t_lst *lst)
{
	t_lst	*curr;

	if (!lst)
		return ;
	curr = lst;
	while (curr)
	{
		printf("%s\n", curr->val);
		curr = curr->next;
	}
}

//free the data of a doubly linked list
void	free_lst(t_lst **lst)
{
	t_lst	*next;

	if (!*lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->val);
		(*lst)->val = NULL;
		free(*lst);
		*lst = NULL;
		*lst = next;
	}
}

//cut out an entree in a doubly linked list
void	cut_lst(t_lst **lst)
{
	t_lst	*prev;
	t_lst	*next;

	if (!*lst)
		return ;
	prev = (*lst)->prev;
	next = (*lst)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free((*lst)->val);
	(*lst)->val = NULL;
	free(*lst);
	*lst = NULL;
	if (!prev && !next)
		lst = NULL;
}

//add an entree to a doubly linked list
int	add2lst(t_lst **lst, char *val)
{
	t_lst	*curr;
	t_lst	*new_lst;

	if (!val)
		return (1);
	if (!*lst)
	{
		*lst = init_lst(val);
		if (!*lst)
			return (0);
		return (1);
	}
	new_lst = init_lst(val);
	if (!new_lst)
		return (0);
	curr = *lst;
	while (curr->next)
		curr = curr->next;
	curr->next = new_lst;
	new_lst->prev = curr;
	return (1);
}

//initialization of a doubly linked list
t_lst	*init_lst(char *val)
{
	t_lst	*lst;

	if (!val)
		return (NULL);
	lst = (t_lst *)ft_calloc(1, sizeof(t_lst));
	if (!lst)
		return (NULL);
	val = ft_strdup(val);
	if (!val)
		return (NULL);
	lst->prev = NULL;
	lst->val = val;
	lst->next = NULL;
	return (lst);
}
