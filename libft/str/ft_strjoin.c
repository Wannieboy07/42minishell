/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:26:56 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/05 13:38:12 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include<stdio.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*rtn;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	rtn = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!rtn)
		return (0);
	ft_memmove(rtn, s1, s1len);
	ft_memmove(rtn + s1len, s2, s2len);
	rtn[s1len + s2len] = '\0';
	free((char *)s1);
	free((char *)s2);
	return (rtn);
}
