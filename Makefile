SRCS =	\
	lexer/handle_identifier.c	\
	lexer/handle_seperator.c	\
	lexer/lexer.c			\
	lexer/lexer_lst.c		\
	lexer/lexer_utils.c		\
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
CLEAR = \033[K

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
	rm -rf $(OBJS_DIR)
	@$(MAKE) fclean -C libft/

fclean: clean
	rm -f $(NAME) $(OUT)


re: fclean all

.PHONY: all clean fclean re
