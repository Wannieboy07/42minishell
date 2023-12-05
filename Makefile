SRCS =	\
	lexer/handle_identifier.c	\
	lexer/handle_seperator.c	\
	lexer/lexer.c				\
	lexer/lexer_lst.c			\
	lexer/lexer_utils.c			\
	\
	parser/parser.c				\
	parser/parser_cmd.c			\
	parser/parser_err.c			\
	parser/parser_free.c		\
	parser/parser_nodes.c		\
	parser/parser_util.c		\
	\
	expander/clean_empties.c	\
	env_lst.c					\
	expander/expander.c			\
	expander/expander_split.c	\
	expander/expander_utils.c	\
	expander/expand_heredoc.c	\
	expander/init_tree.c		\
	expander/strip_quotes.c		\
	\
	exec/check_perm.c			\
	exec/exec_builtin.c			\
	exec/exec.c					\
	exec/exec_cmd.c				\
	exec/exec_redir.c			\
	exec/exec_utils.c			\
	exec/get_path.c				\
	\
	builtins/cd.c				\
	builtins/echo.c				\
	builtins/env.c				\
	builtins/exit.c				\
	builtins/export.c			\
	builtins/pwd.c				\
	builtins/unset.c			\
	\
	error/error_handling.c		\
	error/error_msg.c			\
	\
	signal/signal_handling.c	\

LIBFT = libft/libft.a

NAME = minishell

OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(notdir $(OBJS)))

CC = cc

CC_FLAGS = -Wall -Wextra -Werror -g

UP = \033[A
CUT = \033[K

$(OBJS_DIR)%.o : */%.c minishell.h
	@mkdir -p $(dir $@)
	@echo "\033[38;5;226mCompiling: $(notdir $<)\033[0;39m"
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf "$(UP)$(CUT)"

$(NAME): $(OBJS_PREFIXED) $(LIBFT) main.c
	@echo "\033[0;92mCompiling Done!\033[0;39m"
	@$(CC) $(CC_FLAGS) main.c $(OBJS_PREFIXED) $(LIBFT) -lreadline -o $(NAME)
	@echo "\033[0;92mMiniShell Done!\033[0;39m"


$(LIBFT) :
	@$(MAKE) -sC ./libft

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "\033[0;31mClearing object files\033[0;39m"
	@$(MAKE) fclean -sC libft/

fclean: clean
	@rm -f $(NAME) $(OUT)
	@echo "\033[0;31mClearing executable\033[0;39m"


re: fclean all

.PHONY: all clean fclean re
