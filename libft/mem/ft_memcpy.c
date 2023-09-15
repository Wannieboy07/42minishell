/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:03:05 by wmarien           #+#    #+#             */
/*   Updated: 2023/01/11 09:39:51 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*tdst;
	const char	*tsrc;

	if ((dst == src) || n == 0)
		return (dst);
	if (!dst && !src)
		return (0);
	tdst = (char *)dst;
	tsrc = (const char *)src;
	while (n--)
		tdst[n] = tsrc[n];
	return (dst);
}
