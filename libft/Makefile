# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 13:58:55 by lpeeters          #+#    #+#              #
#    Updated: 2023/11/24 23:10:47 by lpeeters         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#program name (library)
NAME = libft.a

#make into library file
LIBC = ar rcs

#compiler
CC = cc

#flags
CFLAGS = -g -Wall -Wextra -Werror

#remove
RM = rm -rf

#source files
SRCS =	\
		mem/ft_calloc.c				\
		mem/ft_memset.c				\
		mem/ft_bzero.c				\
		mem/ft_memcpy.c				\
		mem/ft_memmove.c 			\
		mem/ft_memchr.c				\
		mem/ft_memcmp.c				\
		mem/free_array.c			\
		\
		ascii/ft_isalpha.c 			\
		ascii/ft_isdigit.c			\
		ascii/ft_isalnum.c			\
		ascii/ft_isascii.c			\
		ascii/ft_isprint.c			\
		ascii/ft_isspace.c			\
		ascii/ft_toupper.c			\
		ascii/ft_tolower.c			\
		\
		str/ft_strlen.c				\
		str/ft_strchr.c				\
		str/ft_strrchr.c			\
		str/ft_strcmp.c				\
		str/ft_strncmp.c			\
		str/ft_strlcpy.c			\
		str/ft_strlcat.c			\
		str/ft_strnstr.c			\
		str/ft_strdup.c				\
		str/ft_substr.c				\
		str/ft_strjoin.c			\
		str/ft_strtrim.c			\
		str/ft_split.c				\
		str/ft_strmapi.c			\
		str/ft_striteri.c			\
		str/cpy_arr.c				\
		str/mk_arr.c				\
		str/strjoin.c				\
		\
		math/ft_atoi.c				\
		math/ft_itoa.c				\
		math/ft_abs.c				\
		\
		put/ft_putchar_fd.c			\
		put/ft_putstr_fd.c			\
		put/ft_putendl_fd.c			\
		put/ft_putnbr_fd.c			\
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
		gnl/get_next_line.c			\

#object directory
OBJ_DIR = OBJS/

#convert c files into object files
OBJS = ${SRCS:%.c=${OBJ_DIR}%.o}

#header file
HEADER = libft.h

#make directories for object files
MK_DIR = mkdir -p ${@D}

#color codes
WHITE = \033[0;39m
YELLOW = \033[38;5;226m
GREEN = \033[0;92m
RED = \033[0;31m

#key codes
UP = \033[A
CLEAR = \033[K

#make object files
${OBJ_DIR}%.o: %.c ${SRCS} ${HEADER}
	@${MK_DIR}
	@echo "${YELLOW}Compiling: $<${WHITE}"
	@${CC} ${CFLAGS} -c $< -o $@
	@printf "${UP}${CLEAR}"

#make project into library file
${NAME}: ${OBJS}
	@echo "${GREEN}Compiling done!${WHITE}"
	@${MK_DIR}
	@${LIBC} ${NAME} ${OBJS} ${HEADER}
	@echo "${GREEN}Libft done!${WHITE}"

#make
all: ${NAME}

#clean object files and directories
clean:
	@${RM} ${OBJ_DIR}
	@echo "${RED}Cleaning unnecessary files${WHITE}"

#clean everything that was made
fclean: clean
	@${RM} ${NAME}
	@echo "${RED}Libft removed!${WHITE}"

#remake
re: fclean all

#targets
.PHONY: all clean fclean re
