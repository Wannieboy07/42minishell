/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:38:07 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/06 14:44:54 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
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

typedef enum e_nodetype
{
	P_PIPE,
	P_CMD
}	t_nodetype;

typedef enum e_iotype
{
	IN,
	OUT,
	HERDOC,
	APPEND
}	t_iotype;

typedef enum e_parse_errtype
{
	MEM = 1,
	SYNTAX
}	t_parse_errtype;

typedef struct s_io_node
{
	t_iotype	type;
	char		*value;
	char		**exp_value;
	int			here_doc;
	void		*prev;
	void		*next;
}	t_io_node;

typedef struct s_node
{
	t_nodetype	type;
	t_io_node	*io_lst;
	char		*args;
	char		**exp_args;
	void		*left;
	void		*right;
}	t_node;

typedef struct s_parse_err
{
	t_parse_errtype	type;
	char			*str;
}	t_parse_err;

/*=== Expander/Executor ===*/

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_ast_dir
{
	TD_LEFT,
	TD_RIGHT
}	t_ast_dir;

typedef enum e_err_msg
{
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_TOO_MANY_ARGS,
	ERRMSG_NUMERIC_REQUI
}	t_err_msg;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}	t_err_no;

typedef struct s_err
{
	t_err_no	no;
	t_err_msg	msg;
	char		*cause;
}	t_err;

typedef struct s_path
{
	t_err	err;
	char	*path;
}	t_path;

/*=== Minishell ===*/

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
}	t_minishell;

extern t_minishell	g_minishell;

void		clean_ms(void);

/*=== Signal Handling ===*/

void		eof_handler(void);
void		init_sighandlers(void);
void		sigquit_handler(int num);

/*=== Error Handling ===*/

int			err_msg(t_err err);
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

//tmp function
void		prnt_ast(t_node *ast);

t_node		*parser(void);

void		set_parse_err(t_parse_errtype type);
void		handle_parse_err(void);

t_node		*get_simple_cmd(void);

void		get_next_token(void);
bool		is_redir(t_tokentype type);
int			get_tokens_prec(void);
int			get_prec(t_tokentype type);
char		*append_args(char *args, char *str);

void		append_io_node(t_io_node **head, t_io_node *io_node);
t_node		*new_node(t_nodetype type);
t_io_node	*new_io_node(t_tokentype type, char *value);
t_iotype	get_iotype(t_tokentype type);

void		clear_ast(t_node **ast);
void		free_cmd_node(t_node *node);

/*=== Expander ===*/

void		init_tree(t_node *node);

char		**expand_args(char *str);
char		*handle_dollar(char *str, size_t *i);

char		*skip_squotes(char *str, size_t *i);
char		*handle_dquotes(char *str, size_t *i);
char		*handle_str(char *str, size_t *i);

char		*clean_empties(char *str);

char		**exp_split(const char *s);

char		*strip_quotes(char *str);

void		expand_heredoc(char *str, int fd);

char		*get_env_val(char *key);
t_env		*envlst_new(char *key, char *value);
void		clear_envlst(void);
void		envlst_addback(t_env *new);
void		update_envlst(char *key, char *value, bool create);

/*=== Execute ===*/

int			exec_node(t_node *tree, bool piped);
int			get_exit_status(int status);

int			exec_simple_cmd(t_node *node, bool piped);

int			exec_builtin(char **args);
bool		is_builtin(char *arg);

int			check_out(t_io_node *io_lst, int *status);
int			check_in(t_io_node *io_lst, int *status);
int			check_append(t_io_node *io_lst, int *status);

t_err		check_exec(char *file, bool cmd);
t_err		check_write(char *file);
t_err		check_read(char *file);

t_path		get_path(char *cmd);

void		*garbage_collector(void *ptr, bool clean);
bool		is_delimiter(char *delim, char *str);

/*=== Builtin ===*/

int			ms_cd(char *path);
int			ms_echo(char **args);
int			ms_env(void);
int			ms_exit(char **args);
int			ms_export(char **argv);
int			ms_pwd(void);
int			ms_unset(char **argv);

void		init_envlst(void);

bool		is_valid_key(char *key);
char		*extract_key(char *str);
char		*extract_value(char *str);

int			check_key(char *str);

#endif
