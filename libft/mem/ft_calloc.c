/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:51:46 by wmarien           #+#    #+#             */
/*   Updated: 2023/03/30 14:51:47 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmeb * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, nmeb * size);
	return (ptr);
}
