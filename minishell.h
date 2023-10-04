/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:40 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/04 23:51:40 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*****************/
/*   libraries   */
/*****************/

//free
# include <stdlib.h>

//boolean
# include <stdbool.h>

//write
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

//consider adding a ZERO macro to the beginning

//words chosen by programmer
//names of built-in commands
// |
// >
// >>
// <
// <<

//macro struct
typedef enum e_tokentype{
	IDENTIFIER,		
	KEYWORD,		
	PIPE,			
	GREAT,			
	D_GREAT,		
	LESS,			
	D_LESS,			
}	t_tokentype;

//token data doubly linked list
typedef struct s_token {
	t_tokentype	type;
	char		*value;
	void		*prev;
	void		*next;
}	t_token;

/*****************/
/*   functions   */
/*****************/

/*=== Signal Handling ===*/

void	eof_handler(void);/*t_main *data*/
void	handle_global_signals(void);
void	handle_cmd_signals(void);

/*=== Error Handling ===*/

int		prnt_err(char *str);
int		lexer_err(t_token **token_lst, char *str, char *err_str);

/*=== Lexer ===*/

int		lexer(char *line);
int		handle_seperator(char **line, t_token **token_lst);
int		handle_identifier(char **line, t_token **token_lst);

t_token	*new_token(t_tokentype type, char *value);
void	token_add_back(t_token **head, t_token *new_node);
void	free_token_lst(t_token **head);

bool	is_seperator(char c);
bool	is_keyword(char *value);

#endif
