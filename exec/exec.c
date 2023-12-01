/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:10:24 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/01 17:11:45 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pipe_child(t_node *node, int fds[2], t_ast_dir dir)
{
	int	status;

	if (dir == TD_LEFT)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
	else if (dir == TD_RIGHT)
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	status = exec_node(node, true);
	(clean_ms(), exit(status));
}

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
			(close(fds[0]), close(fds[1]),
				waitpid(pid_l, &status, 0), waitpid(pid_r, &status, 0));
			g_minishell.sigint_child = false;
			return (get_exit_status(status));
		}
	}
	return (ENO_GENERAL);
}

int	exec_node(t_node *tree, bool piped)
{
	if (!tree)
		return (1);
	if (tree->type == P_PIPE)
		return (exec_pipeline(tree));
	else
		return (exec_simple_cmd(tree, piped));
	return (ENO_GENERAL);
}
