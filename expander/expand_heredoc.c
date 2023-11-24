/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:53:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/24 15:53:55 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_var_expand(char *str, int i, int fd)
{
	int		start;
	char	*val;

	start = ++i;
	if (str[i] == '?')
		return (ft_putnbr_fd(g_minishell.exit_code, fd), 2);
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	if (i != start)
	{
		val = garbage_collector(ft_substr(str, start, i), false);
		val = get_env_val(val);
		if (val)
			ft_putstr_fd(val, fd);
	}
	return (i);
}

void	expand_heredoc(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i += heredoc_var_expand(str, i, fd);
		else
			i += (ft_putchar_fd(str[i], fd), 1);
	}
	ft_putchar_fd('\n', fd);
}
