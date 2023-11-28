/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:15:33 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/28 14:53:37 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h"

//static int	pipe_handler(t_node *ast)
//{
	//int		pfd[2];
	//pid_t	lcmd;
	//pid_t	rcmd;
	//int		lstatus;
	//int		rstatus;

	//if (pipe(pfd) < 0)
		//return (perror("pipe"), 0);
	//lcmd = fork();
	//if (lcmd < 0)
		//return (perror("fork"), 0);
	//if (!lcmd)
	//{
		//if (!redir(IN, pfd))
			//exit(EXIT_FAILURE);
		//ast = ast->left;
		//exec_ext(ast->exp_args);
		//exit(EXIT_FAILURE);
	//}
	//waitpid(lcmd, &lstatus, 0);
	//if (lstatus != 0)
		//return (prnt_err("cmd", NULL), 1);
	//rcmd = fork();
	//if (rcmd < 0)
		//return (perror("fork"), 0);
	//if (!rcmd)
	//{
		//if (!redir(OUT, pfd))
			//exit(EXIT_FAILURE);
		//ast = ast->right;
		//exec_ext(ast->exp_args);
		//exit(EXIT_FAILURE);
	//}
	//waitpid(rcmd, &rstatus, 0);
	//if (rstatus != 0)
		//return (prnt_err("cmd", NULL), 1);
	//return (1);
//}
