/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:02:16 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/01 16:54:44 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long	ft_atoi(const char *nptr)
{
	unsigned long	i;
	unsigned long	nbr;
	int				sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (nptr[i] != '\0' && (nptr[i] == 32
			|| nptr[i] == '\t' || nptr[i] == '\n'
			|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f'))
		i++;
	if (nptr[i] != '\0' && nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && ft_isdigit(nptr[i]))
		nbr = (nbr * 10) + (nptr[i++] - '0');
	return ((int)(nbr * sign));
}
