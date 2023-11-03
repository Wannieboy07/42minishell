/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:06:30 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/03 20:46:46 by lpeeters         ###   ########.fr       */
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
		free(lst);
		lst = next;
	}
}

//add an entree to the export environment's doubly linked list
int	add_val2exp_lst(t_exp_env *lst, char *val)
{
	t_exp_env	*curr;
	t_exp_env	*new_lst;

	if (!lst || !val)
		return (1);
	new_lst = init_exp_lst(val);
	if (!new_lst)
		return (0);
	curr = lst;
	while (curr->next)
		curr = curr->next;
	curr->next = new_lst;
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
	lst->var = var;
	return (lst);
}
