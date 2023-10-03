
#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"

typedef enum e_tokentype{
	IDENTIFIER,		//words chosen by programmer
	KEYWORD,		//names of built-in commands
	PIPE,			// |
	GREAT,			// >
	D_GREAT,		// >>
	LESS,			// <
	D_LESS,			// <<
}	t_tokentype;

typedef struct s_token {
	t_tokentype	type;
	char		*value;
	void		*prev;
	void		*next;
}	t_token;

/*=== Signal Handling ===*/

void	eof_handler(/*t_main *data*/);
void	handle_global_signals(void);
void	handle_cmd_signals(void);

/*=== Error Handling ===*/

int	prnt_err(char *str);
int	lexer_err(t_token **token_lst, char *str, char *err_str);

/*=== Lexer ===*/

int	lexer(char *line);
int	handle_seperator(char **line, t_token **token_lst);
int	handle_identifier(char **line, t_token **token_lst);

t_token	*new_token(t_tokentype type, char *value);
void	token_add_back(t_token **head, t_token *new_node);
void	free_token_lst(t_token **head);

bool	is_seperator(char c);
bool	is_keyword(char *value);

#endif
