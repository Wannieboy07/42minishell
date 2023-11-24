/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:53:43 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/24 15:53:44 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_str(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_dquote_str(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_dquotes(char *str, size_t *i)
{
	char	*ret;

	ret = ft_strdup("\"");
	(*i)++;
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			ret = ft_strjoin(ret, handle_dollar(str, i));
		else
			ret = ft_strjoin(ret, handle_dquote_str(str, i));
	}
	(*i)++;
	return (ft_strjoin(ret, ft_strdup("\"")));
}

char	*skip_squotes(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[++(*i)] != '\'')
		;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}
