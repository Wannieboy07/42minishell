/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:51:08 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/05 12:54:01 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_out(t_io_node *io_lst, int *status)
{
	int	fd;

	if (!io_lst->exp_value || io_lst->exp_value[1])
	{
		*status = err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS,
				io_lst->value});
		return (*status);
	}
	fd = open(io_lst->exp_value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		*status = err_msg(check_write(io_lst->exp_value[0]));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

int	check_in(t_io_node *io_lst, int *status)
{
	int	fd;

	if (!io_lst->exp_value || io_lst->exp_value[1])
	{
		*status = err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS,
				io_lst->value});
		return (*status);
	}
	fd = open(io_lst->exp_value[0], O_RDONLY);
	if (fd == -1)
	{
		*status = err_msg(check_read(io_lst->exp_value[0]));
		return (*status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

int	check_append(t_io_node *io_lst, int *status)
{
	int	fd;

	if (!io_lst->exp_value || io_lst->exp_value[1])
	{
		*status = err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS,
				io_lst->value});
		return (*status);
	}
	fd = open(io_lst->exp_value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		*status = err_msg(check_write(io_lst->exp_value[0]));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}
