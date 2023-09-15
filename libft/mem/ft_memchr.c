/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:33:54 by wmarien           #+#    #+#             */
/*   Updated: 2023/01/20 10:58:23 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str;
	size_t		i;
	char		a;

	str = (const char *)s;
	a = (char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == a)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
