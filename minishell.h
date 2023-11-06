/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:38:07 by wmarien           #+#    #+#             */
/*   Updated: 2023/11/06 05:08:09 by lpeeters         ###   ########.fr       */
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

//PATH_MAX
# include <limits.h>

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

//token types enumeration macro
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

//node types enumeration macro
typedef enum e_nodetype
{
	P_PIPE,
	P_CMD
}	t_nodetype;

//input/output type enumeration macro
typedef enum e_iotype
{
	IN,
	OUT,
	HERDOC,
	APPEND
}	t_iotype;

//error type enumeration macro
typedef enum e_parse_errtype
{
	MEM = 1,
	SYNTAX
}	t_parse_errtype;

/*****************/
/*    structs    */
/*****************/

//input data doubly linked list
typedef struct s_token
{
	t_tokentype	type;
	char		*value;
	void		*prev;
	void		*next;
}	t_token;

//input/output data doubly linked list
typedef struct s_io_node
{
	t_iotype	type;
	char		*value;
	char		**exp_value;
	int			here_doc;
	void		*prev;
	void		*next;
}	t_io_node;

//abstract syntax tree data doubly linked list
typedef struct s_node
{
	t_nodetype	type;
	t_io_node	*io_lst;
	char		*args;
	char		**exp_args;
	void		*left;
	void		*right;
}	t_node;

//export environment doubly linked list
typedef struct s_exp_env
{
	char				*var;
	struct s_exp_env	*prev;
	struct s_exp_env	*next;
}	t_exp_env;

//parse error data structure
typedef struct s_parse_err
{
	t_parse_errtype	type;
	char			*str;
}	t_parse_err;

//minishell data structure
typedef struct s_minishell
{
	char		*line;
	t_token		*tokens;
	t_token		*curr_token;
	t_node		*ast;
	int			exit_code;
	t_parse_err	parse_err;
	int			fdin;
	int			fdout;
	char		**envv;
	t_exp_env	*exp_env;
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
int			init_minishell(char **env);

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
int			prnt_err(char *str, char **av);

/*=== ./lexer/ ===*/

/*******************/
/*     lexer.c     */
/*******************/

//print an input linked list and it's data
void		print_lst(t_token *token_lst);

//pre-parsing by tokenizing the input line
t_token		*lexer(void);

/**********************/
/* handle_seperator.c */
/**********************/

//store tokens in an input doubly linked list
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

//create a new entree to an input doubly linked list
t_token		*new_token(t_tokentype type, char *value);

//add an entree to an input doubly linked list
void		token_add_back(t_token **head, t_token *new_node);

//free an input doubly linked list
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

//print an error specific to unclosed quotation marks
void		prnt_quote_err(void);

/*=== ./parser/ ===*/

/********************/
/*     parser.c     */
/********************/

//combine two nodes into one
t_node		*combine_atoms(t_node *left, t_node *right);

//parse an atomic expression
t_node		*parse_atom(void);

//parse and combine expressions
t_node		*parse_expr(int min_prec);

//parse input and create an abstract syntax tree
t_node		*parser(void);

/********************/
/*   parser_err.c   */
/********************/

//set parsing error type
void		set_parse_err(t_parse_errtype type);

//handle parsing errors and free dynamically allocated memory
void		handle_parse_err(void);

/********************/
/*   parser_cmd.c   */
/********************/

//parse and populate input output doubly linked list
bool		get_io_lst(t_io_node **io_lst);

//join arguments into a single string
bool		join_args(char	**args);

//parse a simple command and it's arguments
t_node		*get_simple_cmd(void);

/*******************/
/*  parser_util.c  */
/*******************/

//join two strings into one with a space between them
char		*append_args(char *args, char *str);

//advance to the next entree of an input doubly linked list
void		get_next_token(void);

//check if token is of redirection type
bool		is_redir(t_tokentype type);

//fetch precedence of a token type
int			get_prec(t_tokentype type);

//fetch precedence of a token
int			get_tokens_prec(void);

/********************/
/*  parser_nodes.c  */
/********************/

//determine input/output type
t_iotype	get_iotype(t_tokentype type);

//create a new entree to an abstract syntax tree doubly linked list
t_node		*new_node(t_nodetype type);

//create a new entree to an input/output doubly linked list
t_io_node	*new_io_node(t_tokentype type, char *value);

//add an entree to an input/output doubly linked list
void		append_io_node(t_io_node **head, t_io_node *io_node);

/*******************/
/*  parser_free.c  */
/*******************/

//free the memory of an input/output doubly linked list
void		free_io_lst(t_io_node **head);

//free all the memory associated with a command's data
void		free_cmd_node(t_node *node);

//free the memory of an abstract syntax tree doubly linked list
void		free_ast_nodes(t_node *node);

//free all the memory associated with an abstract syntax tree
void		clear_ast(t_node **ast);

/*=== ./executor/ ===*/

/********************/
/*    executor.c    */
/********************/

//execute built-in commands
int			exec_builtin(t_node *ast);

//execute commands if any are found
int			exec_cmd(t_node *ast);

//parse linked list and execute commands
int			executor(void);

/*********************/
/* data_management.c */
/*********************/

//printing of export environment's doubly linked list
void		prnt_exp_lst(t_exp_env *lst);

//free the data of an export list doubly linked list
void		free_exp_lst(t_exp_env *lst);

//cut out an entree in the export environment's doubly linked list
void		cut_exp_lst(t_exp_env *lst);

//add an entree to the export environment's doubly linked list
int			add_val2exp_lst(t_exp_env *lst, char *val);

//initialization of export environment's doubly linked list
t_exp_env	*init_exp_lst(char *var);

/*===  ./executor/builtins/ ===*/

/*******************/
/*      env.c      */
/*******************/

//print out the environment variable
int			exec_env(void);

/*******************/
/*      pwd.c      */
/*******************/

//print out the current working directory
int			exec_pwd(void);

/********************/
/*      exit.c      */
/********************/

//exit the shell in a clean way
void		exec_exit(void);

/********************/
/*      echo.c      */
/********************/

//print out input
int			exec_echo(void);

/********************/
/*     export.c     */
/********************/

//initialize the export environment
int			init_exp_env(void);

//command to manage the export environment
int			exec_export(void);

/*********************/
/*      unset.c      */
/*********************/

//check whether a variable exists wihtin the environment
int			check_var(char *var);

//command to remove variables
int			exec_unset(void);

/********************/
/*       cd.c       */
/********************/

//command to change directory
int			exec_cd(void);

/*=== ./parser/ ===*/

/*********************/
/*   parser_prnt.c   */
/*********************/

//TEST FUNCTION
void		prnt_tabs(int *tabs);

//TEST FUNCTION
void		prnt_node(t_node *node, int *i);

//TEST FUNCTION
void		prnt_ast(t_node	*ast);

#endif
