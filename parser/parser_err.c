/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:19:26 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/01 15:39:19 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_parse_err(t_parse_errtype type)
{
	g_minishell.parse_err.type = type;
}

void	handle_parse_err(void)
{
	t_parse_errtype	err_type;
	t_tokentype		t_type;
	char			**types;

	types = (char *[]){"IDENTIFIER", "|", ">", ">>", "<", "<<", "newline"};
	err_type = g_minishell.parse_err.type;
	(void)t_type;
	(void)types;
	if (err_type)
	{
		if (err_type == SYNTAX)
		{
			if (!g_minishell.curr_token)
				t_type = NL;
			else
				t_type = g_minishell.curr_token->type;
			ft_putstr_fd("\033[31m» \033[36mminishell:\033[0;97m", 2);
			ft_putstr_fd("syntax error near unexpected token '", 2);
			ft_putstr_fd(types[t_type], 2);
			ft_putendl_fd("'", 2);
			g_minishell.exit_code = 258;
		}
		clear_ast(&g_minishell.ast);
		ft_bzero(&g_minishell.parse_err, sizeof(t_parse_err));
	}
}
