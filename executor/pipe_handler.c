/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:01:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/28 19:03:40 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h"

////pipe redirector
//static int	redir(int fd, int *pfd)
//{
	//if (!pfd)
		//return (1);
	//if (fd == IN)
		//if (close(pfd[IN]) < 0 || dup2(pfd[OUT], STDOUT_FILENO) < 0)
			//return (perror("redir in"), 0);
	//if (fd == OUT)
		//if (close(pfd[OUT]) < 0 || (dup2(pfd[IN], STDIN_FILENO) < 0))
			//return (perror("redir out"), 0);
	//return (1);
//}

////logical piping handler
//static int	pipe_handler(t_node *ast, int fd, int *pfd)
//{
	//pid_t	pid;
	//int		status;

	//pid = fork();
	//if (pid < 0)
		//return (perror("fork"), 0);
	//if (!pid)
	//{
		//if (fd != -1)
			//if (!redir(fd, pfd))
				//exit(EXIT_FAILURE);
		//exec_ext(ast->exp_args);
		//exit(EXIT_FAILURE);
	//}
	//if (fd == OUT)
		//if (close(pfd[IN]) < 0 || close(pfd[OUT]) < 0)
			//return (perror("close"), 0);
	//waitpid(pid, &status, 0);
	//if (status != 0)
		//return (status);
	//return (0);
//}

////TESTING
//static void	tester(t_node *ast)
//{
	//t_node	*test;

	//test = ast;
	//if (test->type == P_CMD)
	//{
		//printf("cmd: %s\n", test->exp_args[0]);
		//if (test->left)
			//tester(test->left);
		//if (test->right)
			//tester(test->right);
	//}
	//else if (test->type == P_PIPE)
	//{
		//if (test->left)
			//tester(test->left);
		//if (test->right)
			//tester(test->right);
	//}
//}

////execute external commands
//int	exec_cmd(t_node *ast)
//{
	//int		pfd[2];
	//int		status;

	//if (!ast)
		//return (1);
	//tester(ast);
	//if (pipe(pfd) < 0)
		//return (perror("pipe"), 0);
	//status = pipe_handler(ast->left, IN, pfd);
	//if (status != 0)
		//return (prnt_err("cmd", NULL), 0);
	//status = pipe_handler(ast->right, OUT, pfd);
	//if (status != 0)
		//return (prnt_err("cmd", NULL), 0);
	//return (g_minishell.exit_code = 0, 1);
//}

	////if (ast->type == P_PIPE)
	////{
	////}
	////else
	////{
		////if (!pipe_handler(ast, -1, NULL))
			////return (0);
		////return (g_minishell.exit_code = 0, 1);
	////}
