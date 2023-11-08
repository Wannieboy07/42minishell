/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:17:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/08 04:09:01 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//WIP
//currently just testing
int	var_test(void)
{
	if (!ft_strchr(g_minishell.ast->args, '='))
		return (1);
	if (!check_var(g_minishell.ast->args, g_minishell.var_lst))
	{
		printf("test: new variable\n");
		return (add2lst(&g_minishell.var_lst, g_minishell.ast->args));
	}
	printf("test: variable exists\n");
	return (1);
}
