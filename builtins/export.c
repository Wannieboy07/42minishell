/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:45:28 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/04 16:33:31 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_lst(void)
{
	t_env	*lst;
	size_t	i;

	lst = g_minishell.env_lst;
	while (lst)
	{
		if (lst->value != NULL && (ft_strcmp(lst->key, "_") != 0))
		{
			printf("declare -x %s=\"", lst->key);
			i = 0;
			while ((lst->value)[i])
			{
				if ((lst->value)[i] == '$' || (lst->value)[i] == '"')
					printf("\\%c", (lst->value)[i++]);
				else
					printf("%c", (lst->value[i++]));
			}
			printf("\"\n");
		}
		else if (lst->value == NULL && (ft_strcmp(lst->key, "_") != 0))
			printf("declare -x %s\n", lst->key);
		lst = lst->next;
	}
}

int	export_err_msg(char *identifier)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	check_key(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ms_export(char **argv)
{
	int		i;
	int		exit_s;
	char	*key;

	exit_s = 0;
	i = 1;
	if (!argv[1])
		return (export_lst(), 0);
	while (argv[i])
	{
		if (check_key(argv[i]) == 0)
			exit_s = export_err_msg(argv[i]);
		else
		{
			key = extract_key(argv[i]);
			if (is_valid_key(key))
				update_envlst(key, extract_value(argv[i]), false);
			else
				update_envlst(key, extract_value(argv[i]), true);
		}
		i++;
	}
	return (exit_s);
}
