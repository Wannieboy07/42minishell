/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:42:20 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/01 17:09:22 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_lst(char *key)
{
	t_env	*curr;
	t_env	*prev;

	prev = NULL;
	curr = g_minishell.env_lst;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
		{
			if (prev)
				prev->next = curr->next;
			else
				g_minishell.env_lst = curr->next;
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ms_unset(char **argv)
{
	int		i;
	bool	err;

	i = 1;
	if (!argv[1])
		return (0);
	err = false;
	while (argv[i])
	{
		if (!check_key(argv[i]))
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			err = true;
		}
		else
			unset_lst(garbage_collector(extract_key(argv[i]), false));
		i++;
	}
	return (err);
}
