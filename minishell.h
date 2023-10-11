/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:38:07 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/11 23:36:49 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define GREEN "\033[0;92m"
# define RED "\033[0;31m"
# define CYAN "\033[0;36m"
# define B_CYAN "\033[1;36m"
# define WHITE "\033[0;97m"
# define GREY "\033[0;39m"

# define D_QUOTES 34
# define S_QUOTES 39

typedef enum e_tokentype
{
	ZERO,
	IDENTIFIER,		
	KEYWORD,		
	PIPE,			
	GREAT,			
	D_GREAT,		
	LESS,			
	D_LESS,			
}	t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*value;
	void		*prev;
	void		*next;
}	t_token;

typedef struct s_minishell
{
	char	*line;
	t_token	*tokens;
	int		exit_code;
	int		fdin;
	int		fdout;
	char	**envv;
}	t_minishell;

extern t_minishell	g_minishell;

/*=== Signal Handling ===*/

void		eof_handler(void);
void		handle_global_signals(void);
void		handle_cmd_signals(void);

/*=== Error Handling ===*/

int			prnt_err(char *str);

/*=== Lexer ===*/

t_token		*lexer(void);
int			handle_seperator(char **line, t_token **token_lst);
int			handle_identifier(char **line, t_token **token_lst);

t_token		*new_token(t_tokentype type, char *value);
void		token_add_back(t_token **head, t_token *new_node);
void		free_token_lst(t_token **head);

bool		skip_quotes(char *buff, size_t *i);
void		skip_spaces(char **line);
bool		is_seperator(char *c);
t_tokentype	is_keyword(char *value);
void		prnt_quote_err(void);

#endif
