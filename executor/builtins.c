/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:31:37 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/30 23:24:29 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//print out the environment variable
int	exec_env(void)
{
	int	i;

	if (!g_minishell.envv)
		return (0);
	i = 0;
	while (g_minishell.envv[i])
	{
		printf("%s\n", g_minishell.envv[i]);
		i++;
	}
	return (1);
}

//print out the current working directory
int	exec_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		return (0);
	printf("%s\n", cwd);
	return (1);
}

//exit the shell in a clean way
void	exec_exit(void)
{
	free_token_lst(&g_minishell.tokens);
	free_exp_lst(g_minishell.exp_env);
	free_ast_nodes(g_minishell.ast);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

//print out input
int	exec_echo(t_node *ast)
{
	int	i;

	if (strncmp(ast->args, "echo -n ", 8))
	{
		prnt_err("echo: invalid flag", NULL);
		return (0);
	}
	i = 7;
	while (ast->args[++i])
		printf("%c", ast->args[i]);
	return (1);
}

//print out the export environment variable
int	exec_export(void)
{
	t_exp_env	*exp_lst;
	int			i;

	if (!g_minishell.envv)
		return (0);
	exp_lst = init_exp_lst(g_minishell.envv[0]);
	if (!exp_lst)
		return (0);
	i = 0;
	while (g_minishell.envv[++i])
		add_val2exp_lst(exp_lst, g_minishell.envv[i]);
	g_minishell.exp_env = exp_lst;
	prnt_exp_lst(exp_lst);
	return (1);
}
