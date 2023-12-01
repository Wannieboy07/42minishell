/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:46:44 by wmarien           #+#    #+#             */
/*   Updated: 2023/01/20 12:17:53 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n_len;
	char	*hay;

	i = 0;
	hay = (char *)big;
	n_len = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	if (len == 0)
		return (0);
	while (hay[i] != '\0' && i < len)
	{
		j = 0;
		while (hay[i + j] != '\0' && little[j] != '\0'
			&& hay[i + j] == little[j] && i + j < len)
			j++;
		if (j == n_len)
			return (hay + i);
		i++;
	}
	return (0);
}
