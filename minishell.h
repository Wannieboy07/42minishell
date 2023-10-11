/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:38:07 by wmarien           #+#    #+#             */
/*   Updated: 2023/10/12 00:31:14 by lpeeters         ###   ########.fr       */
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
/*     macros    */
/*****************/

//colors
# define GREEN "\033[0;92m"
# define RED "\033[0;31m"
# define CYAN "\033[0;36m"
# define B_CYAN "\033[1;36m"
# define WHITE "\033[0;97m"
# define GREY "\033[0;39m"

//quotes
# define D_QUOTES 34
# define S_QUOTES 39

//enumeration macro
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

/*****************/
/*    structs    */
/*****************/

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

/***************************/
/*                         */
/*        FUNCTIONS        */
/*                         */
/***************************/

/*=== ./ ===*/

/******************/
/*     main.c     */
/******************/

//initialize minishell data struct variables
void		init_minishell(char **env);

//prompt that takes inputs
int			minishell_loop(void);

//parse inputs, execute commands, handle redirections
int			main(int ac, char **av, char **env);

/*=== ./signal/ ===*/

/*********************/
/* signal_handling.c */
/*********************/

//handle end of of file signal
void		eof_handler(void);

//handle interuption signal whilst executing commands
void		cmd_sig_handler(int signum);

//handle signals whilst executing commands
void		handle_cmd_signals(void);

//handle interuption signal in the command line
void		global_sig_handler(int signum);

//handle signals in the command line
void		handle_global_signals(void);

/*=== ./error/ ===*/

/********************/
/* error_handling.c */
/********************/

//print errors
int			prnt_err(char *str);

/*=== ./lexer/ ===*/

/*******************/
/*     lexer.c     */
/*******************/

//print a linked list and it's data
void		print_lst(t_token *token_lst);

//pre-parsing by tokenizing the input line
t_token		*lexer(void);

/**********************/
/* handle_seperator.c */
/**********************/

//store tokens in a doubly linked list
int			add_seperator(t_tokentype type, char **line, t_token **token_lst);

//tokenize operators from the input
int			handle_seperator(char **line, t_token **token_lst);

/***********************/
/* handle_identifier.c */
/***********************/

//parse input, identify token and store data
int			handle_identifier(char	**line, t_token **token_lst);

/*******************/
/*   lexer_lst.c   */
/*******************/

//create a new entree to a doubly linked list
t_token		*new_token(t_tokentype type, char *value);

//add an entree to a doubly linked list
void		token_add_back(t_token **head, t_token *new_node);

//free a doubly linked list
void		free_token_lst(t_token **head);

/*******************/
/*  lexer_utils.c  */
/*******************/

//parse buffer till the next quote, skipping other quote type
bool		skip_quotes(char *buff, size_t *i);

//skip over any amount of spaces that were found
void		skip_spaces(char **line);

//check if character is any sort seperator
bool		is_seperator(char *c);

//check if character is any sort keyword
t_tokentype	is_keyword(char *value);

//print an error specific to unclosed quotation marks
void		prnt_quote_err(void);

#endif
