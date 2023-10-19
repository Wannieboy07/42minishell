/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:38:07 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/19 17:15:43 by wmarien          ###   ########.fr       */
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

/*=== Lexer ===*/

typedef enum e_tokentype
{
	IDENTIFIER,
	PIPE,
	GREAT,
	D_GREAT,
	LESS,
	D_LESS,
	NL
}	t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*value;
	void		*prev;
	void		*next;
}	t_token;

/*=== Parser ===*/

typedef enum	e_nodetype
{
	P_PIPE,
	P_CMD
}	t_nodetype;

typedef enum	e_iotype
{
	IN,
	OUT,
	HERDOC,
	APPEND
}	t_iotype;

typedef enum	e_parse_errtype
{
	MEM = 1,
	SYNTAX
}	t_parse_errtype;

typedef struct	s_io_node
{
	t_iotype	type;
	char		*value;
	char		**exp_value;
	int			here_doc;
	void	*prev;
	void	*next;
}	t_io_node;

typedef struct	s_node
{
	t_nodetype	type;
	t_io_node	*io_lst;
	char		*args;
	char		**exp_args;
	void	*left;
	void	*right;
}	t_node;

typedef struct	s_parse_err
{
	t_parse_errtype	type;
	char			*str;
}	t_parse_err;

/*=== Minishell ===*/

typedef struct s_minishell
{
	char	*line;
	t_token	*tokens;
	t_token	*curr_token;
	t_node	*ast;
	int		exit_code;
	t_parse_err	parse_err;
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

/*=== Parser ===*/

t_node	*parser(void);

void	set_parse_err(t_parse_errtype type);
void	handle_parse_err(void);

t_node	*get_simple_cmd(void);

void	get_next_token(void);
bool	is_redir(t_tokentype type);
int	get_tokens_prec(void);
int	get_prec(t_tokentype type);
char	*append_args(char *args, char *str);

void	append_io_node(t_io_node **head, t_io_node *io_node);
t_node	*new_node(t_nodetype type);
t_io_node	*new_io_node(t_tokentype type, char *value);
t_iotype	get_iotype(t_tokentype type);

void	clear_ast(t_node **ast);
void	free_cmd_node(t_node *node);

#endif
