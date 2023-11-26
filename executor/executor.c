/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:02:55 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/26 22:04:01 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

////tester function
//static void	prnt_ast_testing(t_node *ast)
//{
	//int	i;

	//if (!ast)
	//{
		//printf("Info: no ast\n");
		//return ;
	//}
	//while (ast->left)
		//ast = ast->left;
	//i = 0;
	//printf("%i: %s\n", i, ast->args);
	//i += 1;
	//while (ast->right)
	//{
		//ast = ast->right;
		//printf("%i: %s\n", i, ast->args);
		//i += 1;
	//}
//}

////tester function
//static void	prnt_nxt_in_ast(t_node *ast)
//{
	//if (ast->right)
	//{
		//ast = ast->right;
		//printf("test: %s\n", ast->args);
	//}
//}

//pipe redirector
static int	redir(int fd, int *pfd)
{
	if (!pfd)
		return (1);
	if (fd == IN)
		if (close(pfd[IN]) < 0 || dup2(pfd[OUT], STDOUT_FILENO) < 0)
			return (perror("redir in"), 0);
	if (fd == OUT)
		if (close(pfd[OUT]) < 0 || (dup2(pfd[IN], STDIN_FILENO) < 0))
			return (perror("redir out"), 0);
	return (1);
}

//logical piping handler
static int	pipe_handler(t_node *ast)
{
	int		pfd[2];
	pid_t	lcmd;
	pid_t	rcmd;
	int		lstatus;
	int		rstatus;

	if (pipe(pfd) < 0)
		return (perror("pipe"), 0);
	lcmd = fork();
	if (lcmd < 0)
		return (perror("fork"), 0);
	if (!lcmd)
	{
		if (!redir(IN, pfd))
			exit(EXIT_FAILURE);
		ast = ast->left;
		exec_ext(ast->exp_args);
		exit(EXIT_FAILURE);
	}
	waitpid(lcmd, &lstatus, 0);
	if (lstatus != 0)
		return (prnt_err("cmd", NULL), 1);
	rcmd = fork();
	if (rcmd < 0)
		return (perror("fork"), 0);
	if (!rcmd)
	{
		if (!redir(OUT, pfd))
			exit(EXIT_FAILURE);
		ast = ast-> right;
		exec_ext(ast->exp_args);
		exit(EXIT_FAILURE);
	}
	if (close(pfd[IN]) < 0 || close(pfd[OUT]) < 0)
		return (perror("close"), 0);
	waitpid(rcmd, &rstatus, 0);
	if (rstatus != 0)
		return (prnt_err("cmd", NULL), 1);
	return (1);
}

//execute external commands
int	exec_cmd(t_node *ast)
{
	if (!ast)
		return (1);
	if (ast->type == P_PIPE)
	{
		if (!pipe_handler(ast))
			return (0);
		return (1);
	}
	//if (!exec_ext(ast->exp_args))
		//return (0);
	return (1);
}

//execute built-in commands
int	exec_builtin(t_node *ast)
{
	if (!ast->args)
		return (1);
	if (!ft_strncmp(ast->args, "echo", 4))
		return (exec_echo());
	else if (!ft_strncmp(ast->args, "cd", 2))
		return (exec_cd());
	else if (!ft_strncmp(ast->args, "pwd", 3))
		return (exec_pwd());
	else if (!ft_strncmp(ast->args, "export", 6))
		return (exec_export());
	else if (!ft_strncmp(ast->args, "unset", 5))
		return (exec_unset());
	else if (!ft_strncmp(ast->args, "set", 3))
		return (exec_set());
	else if (!ft_strncmp(ast->args, "env", 3))
		return (exec_env());
	else if (!ft_strncmp(ast->args, "exit", 4))
		return (exec_exit());
	else
		return (g_minishell.exit_code = 127, 1);
}

	//g_minishell.exit_code = 0;
	//if (!exec_builtin(g_minishell.ast))
		//return (0);
	//if (g_minishell.exit_code != 127)
		//return (1);

//parse linked list and execute commands
int	executor(void)
{
	if (!g_minishell.ast)
		return (1);
	g_minishell.exit_code = 0;
	if (!exec_cmd(g_minishell.ast))
		return (0);
	if (g_minishell.exit_code != 127)
		return (1);
	g_minishell.exit_code = 0;
	if (!var_handler(g_minishell.ast->args))
		return (0);
	if (g_minishell.exit_code != 127)
		return (1);
	return (prnt_err("command not found", NULL), 1);
}
