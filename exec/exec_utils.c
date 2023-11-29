/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:34:55 by wmarien           #+#    #+#             */
/*   Updated: 2023/11/29 10:34:35 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_ptr(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	*garbage_collector(void *ptr, bool clean)
{
	static t_list	*garbage;

	if (clean)
	{
		ft_lstclear(&garbage, free_ptr);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&garbage, ft_lstnew(ptr));
		return (ptr);
	}
}

bool	is_delimiter(char *delim, char *str)
{
	while (*str)
	{
		if (*delim == '\'' || *delim == '"')
		{
			delim++;
			continue ;
		}
		else if (*str == *delim)
		{
			str++;
			delim++;
		}
		else
			return (false);
	}
	while (*delim == '\'' || *delim == '"')
		delim++;
	return (!*delim);
}
