/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:40 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/06 19:11:00 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*****************/
/*   libraries   */
/*****************/

//printf
# include <stdio.h>

//free
# include <stdlib.h>

//boolean
# include <stdbool.h>

//write, dup
# include <unistd.h>

//signal
# include <signal.h>

//readline and associated functions
# include <readline/readline.h>

//add_history
# include <readline/history.h>

//custom libary
# include "libft/libft.h"

/*****************/
/*    structs    */
/*****************/

//words chosen by programmer
//names of built-in commands
// |
// >
// >>
// <
// <<

//macro struct
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

//token data doubly linked list
typedef struct s_token
{
	t_tokentype	type;
	char		*value;
	void		*prev;
	void		*next;
}	t_token;

//minishell data structure
typedef struct s_minishell
{
	char	*line;
	t_token	*tokens;
	int		exit_code;
	int		fdin;
	int		fdout;
	char	**envv;
}	t_minishell;

//make minishell structure able to be accessed globally
extern t_minishell	g_minishell;

/*****************/
/*   functions   */
/*****************/

/*=== Signal Handling ===*/

void		eof_handler(void);/*t_main *data*/
void		handle_global_signals(void);
void		handle_cmd_signals(void);

/*=== Error Handling ===*/

int			prnt_err(char *str);
int			lexer_err(t_token **token_lst, char *str, char *err_str);

/*=== Lexer ===*/

t_token		*lexer(void);
int			handle_seperator(char **line, t_token **token_lst);
int			handle_identifier(char **line, t_token **token_lst);

t_token		*new_token(t_tokentype type, char *value);
void		token_add_back(t_token **head, t_token *new_node);
void		free_token_lst(t_token **head);

bool		skip_quotes(char *buff, size_t *i);
bool		is_seperator(char *c);
t_tokentype	is_keyword(char *value);
void		prnt_quote_err(void);

#endif
