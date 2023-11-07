/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:06:30 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/07 02:39:35 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//printing of export environment's doubly linked list
void	prnt_exp_lst(t_exp_env *lst)
{
	t_exp_env	*curr;

	if (!lst)
		return ;
	curr = lst;
	while (curr)
	{
		printf("%s\n", curr->var);
		curr = curr->next;
	}
}

//free the data of an export list doubly linked list
void	free_exp_lst(t_exp_env *lst)
{
	t_exp_env	*next;

	if (!lst)
		return ;
	while (lst)
	{
		next = lst->next;
		free(lst->var);
		free(lst);
		lst = next;
	}
}

//cut out an entree in the export environment's doubly linked list
void	cut_exp_lst(t_exp_env *curr)
{
	t_exp_env	*prev;
	t_exp_env	*next;

	if (!curr)
		return ;
	prev = curr->prev;
	next = curr->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(curr->var);
	free(curr);
}

//add an entree to the export environment's doubly linked list
int	add_var2exp_lst(t_exp_env *lst, char *var)
{
	t_exp_env	*curr;
	t_exp_env	*new_lst;

	if (!lst || !var)
		return (1);
	new_lst = init_exp_lst(var);
	if (!new_lst)
		return (0);
	curr = lst;
	while (curr->next)
		curr = curr->next;
	curr->next = new_lst;
	new_lst->prev = curr;
	return (1);
}

//initialization of export environment's doubly linked list
t_exp_env	*init_exp_lst(char *var)
{
	t_exp_env	*lst;

	if (!var)
		return (NULL);
	lst = (t_exp_env *)ft_calloc(1, sizeof(t_exp_env));
	if (!lst)
		return (NULL);
	var = ft_strdup(var);
	if (!var)
		return (NULL);
	lst->prev = NULL;
	lst->var = var;
	lst->next = NULL;
	return (lst);
}
