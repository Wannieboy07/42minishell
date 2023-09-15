SRCS = signal_handling.c

LIBFT = libft/libft.a
#FT_PRINTF = ft_printf/libftprintf.a

NAME = lib-minishell
OUT = minishell

OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

CC = cc

CC_FLAGS = -Wall -Wextra -Werror -g 

$(OBJS_DIR)%.o : %.c minishell.h #*headers*#
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling: $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OUT): $(OBJS_PREFIXED) $(LIBFT) test.c
	@echo "\033[0;92mCompiling Done!\033[0;39m"
	@$(CC) $(CC_FLAGS) test.c $(OBJS_PREFIXED) $(LIBFT) -lreadline -o $(OUT)
	@echo "\033[0;92mMiniShell Done!\033[0;39m"

$(LIBFT) :
	@$(MAKE) -C ./libft

$(FT_PRINTF) :
	@$(MAKE) -C ./ft_printf

all:

clean:
	rm -rf $(OBJS_DIR)
	@$(MAKE) clean -C libft/
#	@$(MAKE) clean -C ft_printf/	#

fclean: clean
	rm -f $(NAME) $(OUT)
	@$(MAKE) fclean -C libft/
#	@$(MAKE) fclean -C ft_printf/	#


re: fclean all

.PHONY: all clean fclean re
