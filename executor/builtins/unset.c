/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:20:50 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/23 18:41:41 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Shell variables yet to be impemented.
//command to remove variables
int	exec_unset(void)
{
	t_lst	*vv;

	if (g_minishell.ast->args[5] != '\0' && g_minishell.ast->args[5] != ' ')
		return (g_minishell.exit_code = 127, 1);
	if (g_minishell.ast->args[5] == '\0' || g_minishell.ast->args[5] != ' '
		|| g_minishell.ast->args[6] == '-')
		return (prnt_err("unset: invalid usage", NULL));
	vv = check_var(g_minishell.var_lst, g_minishell.ast->args + 6);
	if (!vv)
		return (1);
	return (cut_lst(&vv), 1);
}
