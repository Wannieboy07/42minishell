/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:17:22 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/05 12:55:53 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir(t_node *node)
{
	t_io_node	*tmp_io;
	int			status;

	tmp_io = node->io_lst;
	while (tmp_io)
	{
		if (tmp_io->type == OUT && check_out(tmp_io, &status) != ENO_SUCCESS)
			return (status);
		else if (tmp_io->type == IN && check_in(tmp_io, &status) != ENO_SUCCESS)
			return (status);
		else if (tmp_io->type == APPEND
			&& check_append(tmp_io, &status) != ENO_SUCCESS)
			return (status);
		else if (tmp_io->type == HERDOC)
			(dup2(tmp_io->here_doc, 0), close(tmp_io->here_doc));
		tmp_io = tmp_io->next;
	}
	return (ENO_SUCCESS);
}

void	reset_stds(bool piped)
{
	if (piped)
		return ;
	dup2(g_minishell.fdin, 0);
	dup2(g_minishell.fdout, 1);
}

int	exec_child(t_node *node)
{
	t_path	path_stat;
	int		status;
	int		fork_pid;

	g_minishell.sigint_child = true;
	fork_pid = fork();
	if (!fork_pid)
	{
		status = check_redir(node);
		if (status != ENO_SUCCESS)
			(clean_ms(), exit(ENO_GENERAL));
		path_stat = get_path((node->exp_args)[0]);
		if (path_stat.err.no != ENO_SUCCESS)
		{
			status = err_msg(path_stat.err);
			(clean_ms(), exit(status));
		}
		if (execve(path_stat.path, node->exp_args, g_minishell.envv) == -1)
			(clean_ms(), exit(1));
	}
	waitpid(fork_pid, &status, 0);
	g_minishell.sigint_child = false;
	return (get_exit_status(status));
}

int	exec_simple_cmd(t_node *node, bool piped)
{
	int	status;

	if (!node->exp_args)
	{
		status = check_redir(node);
		return (reset_stds(piped), (status && ENO_GENERAL));
	}
	else if (is_builtin((node->exp_args)[0]))
	{
		status = check_redir(node);
		if (status != ENO_SUCCESS)
			return (reset_stds(piped), ENO_GENERAL);
		status = exec_builtin(node->exp_args);
		return (reset_stds(piped), status);
	}
	else
		return (exec_child(node));
}
