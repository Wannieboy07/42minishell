/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:40 by lpeeters          #+#    #+#             */
/*   Updated: 2023/10/10 00:35:17 by lpeeters         ###   ########.fr       */
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
# define GREEN "\033[92m"
# define BLUE "\033[1;36m"
# define RED "\033[0;31m"
# define WHITE "\033[0;97m"
# define GREY "\033[0;39m"
# define D_BLUE "\033[0;36m"

//quotes
# define D_QUOTES 34
# define S_QUOTES 39

/*****************/
/*    structs    */
/*****************/

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

/*=== Minishell  ===*/

//initialize minishell data struct variables
void		init_minishell(char **env);

//initialize minishell data struct variables
void		init_minishell(char **env);

//parse inputs, execute commands, handle redirections
int			main(int ac, char **av, char **env);

/*=== Signal Handling ===*/

void		eof_handler(void);
void		handle_global_signals(void);
void		handle_cmd_signals(void);

/*=== Error Handling ===*/

//print errors
int			prnt_err(char *str);
int			lexer_err(t_token **token_lst, char *str, char *err_str);

/*=== Lexer ===*/

//print a linked list and it's data
void		print_lst(t_token *token_lst);

//pre-parsing by tokenizing the input line
t_token		*lexer(void);

/*=== ===*/

//store tokens in doubly linked list
int			add_seperator(t_tokentype type, char **line, t_token **token_lst);

//tokenize input
int			handle_seperator(char **line, t_token **token_lst);

//parse input, identify token and store data
int			handle_identifier(char **line, t_token **token_lst);

/*=== ===*/

//create a new entree to a doubly linked list
t_token		*new_token(t_tokentype type, char *value);

//add an entree to a doubly linked list
void		token_add_back(t_token **head, t_token *new_node);

//free a doubly linked list
void		free_token_lst(t_token **head);

/*=== ===*/

bool		skip_quotes(char *buff, size_t *i);
bool		is_seperator(char *c);
t_tokentype	is_keyword(char *value);
void		prnt_quote_err(void);

#endif
