/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:20:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/03 02:55:12 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//check params of unset for invalid characters
static int	error_unset(char **args)
{
	int	i;

	if (args[1][0] != '_' && !ft_isalpha(args[1][0]))
		return (0);
	i = 0;
	while (args[1][++i])
		if (args[1][i] != '_' && !ft_isalnum(args[1][i]))
			return (0);
	return (1);
}

//command to remove variables
int	exec_unset(char **args)
{
	t_lst	*vv;

	if (args[1] == NULL)
		return (1);
	if (!error_unset(args))
		return (prnt_err("unset: invalid usage", NULL));
	vv = check_var(g_minishell.var_lst, args[1]);
	if (!vv)
		return (printf("test\n"), 1);
	return (cut_lst(&vv), 1);
}
