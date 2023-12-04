/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:20:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/04 15:42:54 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//command to remove variables
int	exec_unset(char **args)
{
	t_lst	*vv;
	int		i;

	if (args[1] == NULL)
		return (1);
	i = 0;
	while (args[++i])
	{
		if (err_var(args[i]))
		{
			prnt_arg_err("unset", args[i], "syntax error");
			continue ;
		}
		vv = check_var(g_minishell.var_lst, args[i]);
		if (vv)
			cut_lst(&vv);
	}
	return (1);
}
