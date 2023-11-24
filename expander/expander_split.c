/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:53:29 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/24 15:53:37 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_str(const char *s, size_t *i)
{
	char	quotes;

	while (s[*i] && s[*i] != ' ')
	{
		if (s[*i] != '\'' && s[*i] != '"')
			(*i)++;
		else
		{
			quotes = s[(*i)++];
			while (s[(*i)] != quotes)
				(*i)++;
			(*i)++;
		}
	}
}

void	fill_str(char **strs, const char *s, size_t i, size_t j)
{
	char	quotes;
	size_t	k;

	k = 0;
	while (s[i] && s[i] != ' ')
	{
		if (s[i] != '\'' && s[i] != '"')
			strs[j][k++] = s[i++];
		else
		{
			quotes = s[i++];
			strs[j][k++] = quotes;
			while (s[i] != quotes)
				strs[j][k++] = s[i++];
			strs[j][k++] = s[i++];
		}
	}
}

char	**set_strs(char **strs, const char *s)
{
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && strs)
	{
		if (s[i] != ' ')
		{
			start = i;
			skip_str(s, &i);
			strs[j] = ft_calloc(i - start + 1, sizeof(char));
			if (!strs[j])
				return (NULL);
			fill_str(strs, s, start, j);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

char	**exp_split(const char *s)
{
	int		ctr;
	char	**strs;
	char	**tofree;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	ctr = 0;
	while (s[i])
	{
		if (s[i] != ' ' && ++ctr)
			skip_str(s, &i);
		while (s[i] && s[i] == ' ')
			i++;
	}
	strs = ft_calloc(ctr + 1, sizeof(char *));
	tofree = strs;
	strs = set_strs(strs, s);
	if (!strs || !ctr)
		return (free_arr(tofree), NULL);
	return (strs);
}
