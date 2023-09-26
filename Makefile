SRCS = signal_handling.c

LIBFT = libft/libft.a

NAME = minishell

OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

CC = cc

CC_FLAGS = -Wall -Wextra -Werror -g 

$(OBJS_DIR)%.o : %.c minishell.h libft/libft.h #*headers*#
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling: $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJS_PREFIXED) $(LIBFT) test.c
	@echo "\033[0;92mCompiling Done!\033[0;39m"
	@$(CC) $(CC_FLAGS) test.c $(OBJS_PREFIXED) $(LIBFT) -lreadline -o $(NAME)
	@echo "\033[0;92mMiniShell Done!\033[0;39m"

$(LIBFT) :
	@$(MAKE) -C ./libft

$(FT_PRINTF) :
	@$(MAKE) -C ./ft_printf

all:	$(NAME)

clean:
	rm -rf $(OBJS_DIR)
	@$(MAKE) clean -C libft/

fclean: clean
	rm -f $(NAME) $(OUT)
	@$(MAKE) fclean -C libft/


re: fclean all

.PHONY: all clean fclean re
