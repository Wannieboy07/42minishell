SRCS =	\
		mem/ft_calloc.c			\
		mem/ft_memset.c			\
		mem/ft_bzero.c			\
		mem/ft_memcpy.c			\
		mem/ft_memmove.c 		\
		mem/ft_memchr.c			\
		mem/ft_memcmp.c			\
		mem/ft_free_arr.c		\
		\
		ascii/ft_isalpha.c 		\
		ascii/ft_isdigit.c		\
		ascii/ft_isnumber.c		\
		ascii/ft_isalnum.c		\
		ascii/ft_isascii.c		\
		ascii/ft_isprint.c		\
		ascii/ft_isspace.c		\
		ascii/ft_toupper.c		\
		ascii/ft_tolower.c		\
		\
		str/ft_strlen.c			\
		str/ft_strchr.c			\
		str/ft_strcmp.c			\
		str/ft_strrchr.c		\
		str/ft_strncmp.c		\
		str/ft_strlcpy.c		\
		str/ft_strlcat.c		\
		str/ft_strnstr.c		\
		str/ft_strdup.c			\
		str/ft_substr.c			\
		str/ft_strjoin.c		\
		str/ft_strtrim.c		\
		str/ft_split.c			\
		str/ft_strmapi.c		\
		str/ft_striteri.c		\
		str/cpy_arr.c			\
		\
		math/ft_atoi.c			\
		math/ft_itoa.c			\
		math/ft_abs.c			\
		\
		put/ft_putchar_fd.c		\
		put/ft_putstr_fd.c		\
		put/ft_putendl_fd.c		\
		put/ft_putnbr_fd.c		\
		\
		lst/ft_lstnew_bonus.c		\
		lst/ft_lstadd_front_bonus.c	\
		lst/ft_lstsize_bonus.c		\
		lst/ft_lstlast_bonus.c		\
		lst/ft_lstadd_back_bonus.c	\
		lst/ft_lstdelone_bonus.c	\
		lst/ft_lstclear_bonus.c		\
		lst/ft_lstiter_bonus.c		\
		lst/ft_lstmap_bonus.c		\
		\
		gnl/get_next_line.c		\

NAME = libft.a

OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(notdir $(OBJS)))

CC = cc

CC_FLAGS = -Wall -Wextra -Werror

UP = \033[A
CUT = \033[K

$(OBJS_DIR)%.o : */%.c libft.h get_next_line.h
	@mkdir -p $(dir $@)
	@echo "\033[38;5;226mCompiling: $(notdir $<)\033[0;39m"
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf "$(UP)$(CUT)"

$(NAME): $(OBJS_PREFIXED)
	@ar rcs $(NAME) $(OBJS_PREFIXED)
	@echo "\033[0;92mLibft done!\033[0;39m"

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "\033[0;31mClearing object files\033[0;39m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31mClearing library\033[0;39m"

re: fclean all


.PHONY: all clean fclean re
