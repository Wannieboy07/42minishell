/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:20:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/03 22:13:29 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//check params of unset for syntax errors
static int	err_unset(char **args)
{
	int	i;
	int	j;

	i = -1;
	while (args[++i])
	{
		j = 0;
		if (args[i][j] != '_' && !ft_isalpha(args[i][j]))
			return (1);
		while (args[i][++j])
			if (args[i][j] != '_' && !ft_isalnum(args[i][j]))
				return (1);
	}
	return (0);
}

//command to remove variables
int	exec_unset(char **args)
{
	t_lst	*vv;
	int		i;

	if (args[1] == NULL)
		return (1);
	if (err_unset(args))
		return (prnt_err("unset: invalid usage", NULL));
	i = -1;
	while (args[++i])
	{
		vv = check_var(g_minishell.var_lst, args[i]);
		if (vv)
			cut_lst(&vv);
	}
	return (1);
}
