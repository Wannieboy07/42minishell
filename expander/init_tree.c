/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:35:08 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/06 14:43:33 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_sig_handler(int signum)
{
	(void)signum;
	clean_ms();
	exit(SIGINT);
}

void	open_heredoc(t_io_node *io, int fd[2])
{
	char	*line;
	char	*quotes;

	signal(SIGINT, heredoc_sig_handler);
	quotes = io->value;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (is_delimiter(io->value, line))
			break ;
		if (!*quotes)
			expand_heredoc(line, fd[1]);
		else
		{
			ft_putstr_fd(line, fd[1]);
			ft_putstr_fd("\n", fd[1]);
		}
	}
	clean_ms();
	exit(0);
}

bool	leave_node(int fd[2], int *pid)
{
	waitpid(*pid, pid, 0);
	signal(SIGQUIT, sigquit_handler);
	g_minishell.sigint_child = false;
	close(fd[1]);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (true);
	return (false);
}

void	init_node(t_node *node)
{
	t_io_node	*io;
	int			fd[2];
	int			pid;

	if (node->args)
		node->exp_args = expand_args(node->args);
	io = node->io_lst;
	while (io)
	{
		if (io->type == HERDOC)
		{
			pipe(fd);
			pid = (signal(SIGQUIT, SIG_IGN), fork());
			if (!pid)
				open_heredoc(io, fd);
			if (leave_node(fd, &pid))
				return ;
			io->here_doc = fd[0];
		}
		else
			io->exp_value = expand_args(io->value);
		io = io->next;
	}
}

void	init_tree(t_node *node)
{
	if (!node)
		return ;
	if (node->type == P_PIPE)
	{
		init_tree(node->left);
		if (!g_minishell.heredoc_sigint)
			init_tree(node->right);
	}
	else
		init_node(node);
}
