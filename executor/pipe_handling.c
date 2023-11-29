/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:01:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/29 23:24:18 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*//TESTING*/
/*static void	tester(t_node *ast)*/
/*{*/
	/*t_node	*test;*/

	/*test = ast;*/
	/*if (test->type == P_CMD)*/
	/*{*/
		/*printf("cmd: %s\n", test->exp_args[0]);*/
		/*if (test->left)*/
			/*tester(test->left);*/
		/*if (test->right)*/
			/*tester(test->right);*/
	/*}*/
	/*if (test->type == P_PIPE)*/
	/*{*/
		/*if (test->left)*/
			/*tester(test->left);*/
		/*if (test->right)*/
			/*tester(test->right);*/
	/*}*/
/*}*/

//pipe redirector
int	redir(int fd, int *pfd, char *path)
{
	if (!pfd || !path)
		return (1);
	if (fd == IN)
		if (close(pfd[IN]) < 0 || dup2(pfd[OUT], STDOUT_FILENO) < 0)
			return (free(path), perror("redir in"), 0);
	if (fd == OUT)
		if (close(pfd[OUT]) < 0 || (dup2(pfd[IN], STDIN_FILENO) < 0))
			return (free(path), perror("redir out"), 0);
	return (1);
}

//logical piping handler
int	pipe_handler(t_node *ast, int fd)
{
	pid_t	pid;
	char	*path;
	int		pfd[2];

	path = check_path(ast->exp_args[0]);
	if (!path)
		return (prnt_err("command not found", NULL), 0);
	if (pipe(pfd) > 0)
		return (0);
	pid = fork();
	if (pid < 0)
		return (free(path), perror("fork"), 0);
	if (!pid)
	{
		if (fd != -1)
			if (!redir(fd, pfd, path))
				exit(EXIT_FAILURE);
		exec_ext(ast->exp_args, path);
		exit(EXIT_FAILURE);
	}
	if (fd == OUT)
		if (close(pfd[IN]) < 0 || close(pfd[OUT]) < 0)
			return (free(path), perror("close"), 0);
	waitpid(pid, &g_minishell.exit_code, 0);
	return (free(path), 1);
}
