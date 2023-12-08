/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:14:40 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/08 12:35:52 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_valid_key(char *key)
{
	t_env	*lst;

	lst = g_minishell.env_lst;
	while (lst)
	{
		if (!ft_strcmp(key, lst->key))
			return (true);
		lst = lst->next;
	}
	return (false);
}

char	*extract_key(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (garbage_collector(ft_substr(str, 0, i), false));
		i++;
	}
	return (garbage_collector(ft_strdup(str), false));
}

char	*extract_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (garbage_collector(
					ft_substr(str, i, ft_strlen(str) - i), false));
		}
		i++;
	}
	return (NULL);
}

void	init_envlst(void)
{
	int		i;
	char	**env;
	char	*key;
	char	*val;

	env = g_minishell.envv;
	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		key = extract_key(env[i]);
		val = extract_value(env[i]);
		update_envlst(key, val, true);
		i++;
	}
}

int	ms_env(void)
{
	t_env	*lst;

	lst = g_minishell.env_lst;
	while (lst)
	{
		if (lst->value)
			printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	return (ENO_SUCCESS);
}
