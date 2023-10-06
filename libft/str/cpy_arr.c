/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:56:52 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/06 20:01:25 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// perror
#include <stdio.h>

char	**cpy_arr(char **arr)
{
	int		i;
	char	**cpy;

	i = 0;
	while (arr[i] != NULL)
		i++;
	cpy = (char **)malloc(sizeof(char *) * (i + 1));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		cpy[i] = ft_strdup(arr[i]);
		if (cpy[i++] == NULL)
		{
			free_arr(cpy);
			return (NULL);
		}
	}
	cpy[i] = NULL;
	return (cpy);
}
