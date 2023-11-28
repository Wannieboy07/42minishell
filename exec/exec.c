/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:10:24 by wmarien           #+#    #+#             */
/*   Updated: 2023/11/28 15:25:22 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	exec_pipeline(t_node *tree)
{
	int	status;
	int	fds[2];
	int	pid_l;
	int	pid_r;

	g_minishell.sigint_child = true;
	pipe(fds);
	pid_l = fork();
	if (!pid_l)
		exec_pipe_child(tree->left, fds, TD_LEFT);
	else
	{
		pid_r = fork();
		if (!pid_r)
			exec_pipe_child(tree->right, fds, TD_RIGHT);
		else
		{
			(close(fds[0]), close(fds[1]), waitpid(pid_l, &status, 0), waitpid(pid_r, &status, 0));
			g_minshell.sigint-child = false;
			return (get_exit_status(status));
		}
	}
	return (ENO_GENERAL);
}

int	exec_node(t_node *tree, bool piped)
{
	int	status;

	if (!tree)
		return (1);
	if (tree->type == P_PIPE)
		return (exec_pipeline(tree));
	else
		return(exec_simple_cmd(tree, piped));
	return (ENO_GENERAL);
}
