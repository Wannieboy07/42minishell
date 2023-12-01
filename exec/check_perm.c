/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_perm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:07:53 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/01 17:03:06 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_err	check_exec(char *file, bool cmd)
{
	if (!*file)
		return ((t_err){ENO_GENERAL, ERRMSG_NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == -1)
			return ((t_err){ENO_CANT_EXEC, ERRMSG_PERM_DENIED, file});
		return ((t_err){ENO_SUCCESS, 19, NULL});
	}
	if (cmd)
		return ((t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, file});
	return ((t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, file});
}

t_err	check_write(char *file)
{
	if (!*file)
		return ((t_err){ENO_GENERAL, ERRMSG_NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return ((t_err){ENO_GENERAL, ERRMSG_PERM_DENIED, file});
		return ((t_err){ENO_SUCCESS, 19, NULL});
	}
	return ((t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, file});
}

t_err	check_read(char *file)
{
	if (!*file)
		return ((t_err){ENO_GENERAL, ERRMSG_NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK) == -1)
			return ((t_err){ENO_GENERAL, ERRMSG_PERM_DENIED, file});
		return ((t_err){ENO_SUCCESS, 19, NULL});
	}
	return ((t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, file});
}
