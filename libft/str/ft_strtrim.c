/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:09:05 by wmarien           #+#    #+#             */
/*   Updated: 2023/01/16 13:24:59 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	a;
	size_t	b;
	char	*rtn;

	if (!s1 || !set)
		return (0);
	a = 0;
	b = ft_strlen(s1) - 1;
	while (a <= b && ft_strchr(set, s1[a]) != 0)
		a++;
	if (a == ft_strlen(s1))
		return (rtn = ft_calloc(1, sizeof(char)));
	while (b > a && ft_strchr(set, s1[b]) != 0)
		b--;
	rtn = ft_substr(s1, a, b - a + 1);
	if (!rtn)
		return (0);
	return (rtn);
}
