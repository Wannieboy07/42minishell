/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:38:07 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/04 15:37:08 by lpeeters         ###   ########.fr       */
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

//write, dup, chdir, getcwd, execve, fork, pipe
# include <unistd.h>

//signal
# include <signal.h>

//PATH_MAX
# include <limits.h>

//waitpid
# include <sys/wait.h>

//stat
# include <sys/stat.h>

//readline and associated functions
# include <readline/readline.h>

//add_history
# include <readline/history.h>

//custom library
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

//var_val
# define VAR 0
# define VAL 1

//check for stat()
# define VALID 0
# define INVALID 1

//identifier for fork()
# define CHILD 0
# define PARENT 1

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

//abstract syntax tree data singly linked list
typedef struct s_node
{
	t_nodetype	type;
	t_io_node	*io_lst;
	char		*args;
	char		**exp_args;
	void		*left;
	void		*right;
}	t_node;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//doubly linked list
typedef struct s_lst
{
	char			*var;
	char			*val;
	bool			exp;
	struct s_lst	*prev;
	struct s_lst	*next;
}	t_lst;

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
	bool		sigint_child;
	bool		heredoc_sigint;
	char		**envv;
	t_env		*env_lst;
	t_lst		*var_lst;
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

//cleanup handler
void		clean_ms(void);

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

//print argument errors
int			prnt_arg_err(char *type, char *arg, char *msg);

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

/*=== ./expander ===*/

/*******************/
/*   init_tree.c   */
/*******************/

void		heredoc_sig_handler(int signum);

void		open_heredoc(t_io_node *io, int fd[2]);

bool		leave_node(int fd[2], int *pid);

void		init_node(t_node *node);

void		init_tree(t_node *node);

/********************/
/*    expander.c    */
/********************/

char		*handle_dollar(char *str, size_t *i);

char		**expand_args(char *str);

char		*expand_var(char *str);

/********************/
/* expander_utils.c */
/********************/

char		*handle_str(char *str, size_t *i);

char		*handle_dquote_str(char *str, size_t *i);

char		*handle_dquotes(char *str, size_t *i);

char		*skip_squotes(char *str, size_t *i);

/*******************/
/* clean_empties.c */
/*******************/

char		*clean_empties(char *str);

/********************/
/* expander_split.c */
/********************/

void		skip_str(const char *s, size_t *i);

void		fill_str(char **strs, const char *s, size_t i, size_t j);

char		**set_strs(char **strs, const char *s);

char		**exp_split(const char *s);

/********************/
/*  strip_quotes.c  */
/********************/

int			unquoted_len(char *str);

char		*strip_quotes(char *str);

/********************/
/* expand_heredoc.c */
/********************/

int			heredoc_var_expand(char *str, int i, int fd);

void		expand_heredoc(char *str, int fd);

/*******************/
/*    env_lst.c    */
/*******************/

char		*get_env_val(char *key);

void		clear_envlst(void);

void		envlst_addback(t_env *new);

t_env		*envlst_new(char *key, char *value);

void		update_envlst(char *key, char *value, bool create);

/*=== ./exec/ ===*/

/********************/
/*   exec_utils.c   */
/********************/

void		*garbage_collector(void *ptr, bool clean);

bool		is_delimiter(char *delim, char *str);

/*=== ./data/ ===*/

/*********************/
/* data_management.c */
/*********************/

//print out a doubly linked list
void		prnt_lst(t_lst *lst, bool exp);

//free the data of a doubly linked list
void		free_lst(t_lst **lst);

//cut out an entree in a doubly linked list
void		cut_lst(t_lst **lst);

//add an entree to a doubly linked list
int			add2lst(t_lst **lst, char *var, char *val, bool exp);

//initialization of a doubly linked list
t_lst		*init_lst(char *var, char *val, bool exp);

/*=== ./variables/ ===*/

/*********************/
/*    variables.c    */
/*********************/

//check if variable exists and change value if it needs to be changed
int			handle_var_val(char *var, char *val, bool exp);

//check whether a value matches for a variable within the environment
t_lst		*check_val(t_lst *lst, char *val);

//check whether a variable exists within the environment
t_lst		*check_var(t_lst *lst, char *var);

//convert variable string to array
char		**var_val(char *var_val);

//logical variable handler
int			var_handler(char **args);

/*=== ./executor/ ===*/

/********************/
/*    executor.c    */
/********************/

//execute built-in commands
int			exec_builtin(char **args);

//execute commands in order
int			ast_parser(t_node *start, t_node *ast, int fd);

//parse linked list and execute commands
int			executor(void);

/*******************/
/* pipe_handling.c */
/*******************/

//logical piping handler
int			pipe_handler(t_node *ast, int fd);

/*===  ./executor/builtins/ ===*/

/*******************/
/*      set.c      */
/*******************/

//print out all the environment variables
int			exec_set(char **args);

/*******************/
/*      env.c      */
/*******************/

//print out the environment variable
int			exec_env(char **args);

/*******************/
/*      pwd.c      */
/*******************/

//print out the current working directory
int			exec_pwd(char **args);

/********************/
/*      exit.c      */
/********************/

//exit the shell in a clean way
int			exec_exit(char **args);

/********************/
/*      echo.c      */
/********************/

//print out input
int			exec_echo(char **args);

/********************/
/*     export.c     */
/********************/

//initialize the export environment
int			init_var_lst(void);

//check params of variables for syntax errors
int			err_var(char *var);

//command to manage the export environment
int			exec_export(char **args);

/*********************/
/*      unset.c      */
/*********************/

//removes variables
int			rm_var(char *var, t_lst *lst);

//command to remove variables
int			exec_unset(char **args);

/********************/
/*       cd.c       */
/********************/

//command to change directory
int			exec_cd(char **args);

/*===  ./executor/externals/ ===*/

/***********************/
/* external_commands.c */
/***********************/

//attempt to find a valid path for the command received in the environment
char		*comp_path(char **paths, char *arg, struct stat fstat);

//check the path of an external command
char		*check_path(char *arg);

//execute external commands
void		exec_ext(char **args, char *path);

/*=== ./parser/ ===*/

/*********************/
/* tmp_parser_prnt.c */
/*********************/

//TEST FUNCTION
void		prnt_tabs(int *tabs);

//TEST FUNCTION
void		prnt_node(t_node *node, int *i);

//TEST FUNCTION
void		prnt_ast(t_node	*ast);

#endif
