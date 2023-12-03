/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:06:30 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/03 02:54:57 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//printing of a doubly linked list
void	prnt_lst(t_lst *lst, bool exp)
{
	t_lst	*curr;

	if (!lst)
		return ;
	curr = lst;
	while (curr)
	{
		if (exp == false)
			printf("%s=%s\n", curr->var, curr->val);
		else if (exp == true)
			if (curr->exp == true)
				printf("%s=%s\n", curr->var, curr->val);
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
		free((*lst)->var);
		(*lst)->var = NULL;
		free((*lst)->val);
		(*lst)->val = NULL;
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
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
	free((*lst)->var);
	(*lst)->var = NULL;
	free((*lst)->val);
	(*lst)->val = NULL;
	(*lst)->exp = false;
	free(*lst);
	*lst = NULL;
}

//add an entree to a doubly linked list
int	add2lst(t_lst **lst, char *var, char *val, bool exp)
{
	t_lst	*curr;
	t_lst	*new_lst;

	if (!var || !val)
		return (1);
	if (!*lst)
	{
		*lst = init_lst(var, val, exp);
		if (!*lst)
			return (0);
		return (1);
	}
	new_lst = init_lst(var, val, exp);
	if (!new_lst)
		return (0);
	curr = *lst;
	while (curr->next)
		curr = curr->next;
	new_lst->prev = curr;
	curr->next = new_lst;
	return (1);
}

//initialization of a doubly linked list
t_lst	*init_lst(char *var, char *val, bool exp)
{
	t_lst	*lst;

	if (!var || !val)
		return (NULL);
	lst = (t_lst *)malloc(sizeof(t_lst));
	if (!lst)
		return (NULL);
	lst->prev = NULL;
	lst->var = ft_strdup(var);
	if (!lst->var)
		return (free(lst), NULL);
	lst->val = ft_strdup(val);
	if (!lst->val)
		return (free(lst), free(lst->var), NULL);
	lst->next = NULL;
	lst->exp = exp;
	return (lst);
}
