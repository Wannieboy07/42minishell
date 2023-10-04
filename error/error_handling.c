/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:04 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/04 23:47:33 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//print a string to the standard error stream
int	prnt_err(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

int	lexer_err(t_token **token_lst, char *str, char *err_str)
{
	if (*token_lst)
		free_token_lst(token_lst);
	if (str)
		free(str);
	if (err_str)
		prnt_err(err_str);
	return (1);
}
