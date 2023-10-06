/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:06:17 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/06 22:45:57 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//free the memory of a 2d array
void	free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
}
