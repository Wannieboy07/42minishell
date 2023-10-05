/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:04 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/05 20:08:49 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//print errors
int	prnt_err(char *str)
{
	write(2, "\033[0;31mError\033[0;39m: ", 22);
	ft_putendl_fd(str, 2);
	return (1);
}

//memory and error handling of the lexer
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
