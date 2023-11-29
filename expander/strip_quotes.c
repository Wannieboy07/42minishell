/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:38:11 by wmarien           #+#    #+#             */
/*   Updated: 2023/11/29 10:38:13 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unquoted_len(char *str)
{
	int		len;
	size_t	i;
	char	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quotes = str[i];
			while (str[++i] && str[i] != quotes)
				len++;
		}
		else
			len += (i++ || 1);
	}
	return (len);
}

char	*strip_quotes(char *str)
{
	char	quotes;
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ret = ft_calloc(unquoted_len(str) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quotes = str[i++];
			while (str[i] != quotes)
				ret[j++] = str[i++];
			i++;
		}
		else
			ret[j++] = str[i++];
	}
	return (free(str), ret);
}
