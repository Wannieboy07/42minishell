/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:20:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/30 19:39:11 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Shell variables yet to be impemented.
//command to remove variables
int	exec_unset(char **args)
{
	t_lst	*vv;

	if (args[0][5] != '\0' && args[0][5] != ' ')
		return (g_minishell.exit_code = 127, 1);
	if (args[0][5] == '\0' || args[0][5] != ' '
		|| args[0][6] == '-')
		return (prnt_err("unset: invalid usage", NULL));
	vv = check_var(g_minishell.var_lst, g_minishell.ast->args + 6);
	if (!vv)
		return (1);
	return (cut_lst(&vv), 1);
}
