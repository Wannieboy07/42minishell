SRCS =	\
	lexer/handle_identifier.c	\
	lexer/handle_seperator.c	\
	lexer/lexer.c			\
	lexer/lexer_lst.c		\
	lexer/lexer_utils.c		\
	\
	parser/parser.c			\
	parser/parser_cmd.c		\
	parser/parser_err.c		\
	parser/parser_free.c		\
	parser/parser_nodes.c		\
	parser/parser_util.c		\
	\
	error/error_handling.c		\
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
	@printf "$(UP) $(CUT)"

$(NAME): $(OBJS_PREFIXED) $(LIBFT) main.c
	@echo "\033[0;92mCompiling Done!\033[0;39m"
	@$(CC) $(CC_FLAGS) main.c $(OBJS_PREFIXED) $(LIBFT) -lreadline -o $(NAME)
	@echo "\033[0;92mMiniShell Done!\033[0;39m"


$(LIBFT) :
	@$(MAKE) -C ./libft

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "\033[0;31mClearing object files\033[0;39m"
	@$(MAKE) fclean -C libft/

fclean: clean
	@rm -f $(NAME) $(OUT)
	@echo "\033[0;31mClearing executable\033[0;39m"


re: fclean all

.PHONY: all clean fclean re
