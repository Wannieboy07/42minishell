/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:28:49 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/08 12:33:57 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_val(char *key)
{
	t_env	*envlst;

	envlst = g_minishell.env_lst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

void	clear_envlst(void)
{
	t_env	*envlst;
	t_env	*lst_tofree;

	envlst = g_minishell.env_lst;
	while (envlst)
	{
		lst_tofree = envlst;
		envlst = envlst->next;
		free(lst_tofree);
	}
	g_minishell.env_lst = NULL;
}

void	envlst_addback(t_env *new)
{
	t_env	*curr;

	if (!g_minishell.env_lst)
	{
		g_minishell.env_lst = new;
		return ;
	}
	curr = g_minishell.env_lst;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}

t_env	*envlst_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = garbage_collector(ft_strdup(key), false);
	if (value)
		new->value = garbage_collector(ft_strdup(value), false);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	update_envlst(char *key, char *value, bool create)
{
	t_env	*envlst;

	envlst = g_minishell.env_lst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
		{
			if (value)
				envlst->value = garbage_collector(ft_strdup(value), false);
			return ;
		}
		envlst = envlst->next;
	}
	if (create)
		envlst_addback(envlst_new(key, value));
}
