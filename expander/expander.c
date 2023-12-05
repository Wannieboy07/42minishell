/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:53:16 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/05 13:44:11 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_dollar(char *str, size_t *i)
{
	size_t	start;
	char	*var;
	char	*env_val;

	(*i)++;
	if (ft_isdigit(str[*i]) || str[*i] == '0')
	{
		(*i)++;
		return (ft_strdup(""));
	}
	else if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_minishell.exit_code));
	}
	else if (!ft_isalnum(str[*i]) || str[*i] != '_')
		return (ft_strdup("$"));
	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, start, *i - start);
	env_val = get_env_val(var);
	if (!env_val)
		return (free(var), ft_strdup(""));
	return (free(var), ft_strdup(env_val));
}

char	*expand_var(char *str)
{
	char	*ret;
	size_t	i;

	ret = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = ft_strjoin(ret, skip_squotes(str, &i));
		else if (str[i] == '"')
			ret = ft_strjoin(ret, handle_dquotes(str, &i));
		else if (str[i] == '$')
			ret = ft_strjoin(ret, handle_dollar(str, &i));
		else
			ret = ft_strjoin(ret, handle_str(str, &i));
	}
	return (ret);
}

char	**expand_args(char *str)
{
	char	**exp;
	size_t	i;

	str = expand_var(str);
	if (!str)
		return (NULL);
	str = clean_empties(str);
	if (!str)
		return (NULL);
	exp = exp_split(str);
	free(str);
	if (!exp)
		return (NULL);
	i = 0;
	while (exp[i])
	{
		exp[i] = strip_quotes(exp[i]);
		i++;
	}
	return (exp);
}
