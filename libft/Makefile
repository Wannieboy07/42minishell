# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 13:58:55 by lpeeters          #+#    #+#              #
#    Updated: 2023/10/04 22:11:12 by lpeeters         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#program name (library)
NAME = libft.a

#make into library file
LIBC = ar rcs

#compiler
CC = gcc

#flags
CFLAGS = -g -Wall -Wextra -Werror

#remove
RM = rm -rf

#source files
SRCS = ${shell find . -name "*.c"}

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
