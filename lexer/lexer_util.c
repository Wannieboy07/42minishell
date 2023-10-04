/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:20 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/04 16:19:57 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_seperator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_keyword(char *value)
{
	if (!ft_strncmp(value, "echo", 4) || !ft_strncmp(value, "cd", 2)
		|| !ft_strncmp(value, "pwd", 3) || !ft_strncmp(value, "export", 6)
		|| !ft_strncmp(value, "unset", 5) || !ft_strncmp(value, "env", 3)
		|| !ft_strncmp(value, "exit", 4))
		return (true);
	else
		return (false);
}
