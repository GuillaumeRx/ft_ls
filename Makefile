# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guroux <guroux@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/31 17:49:13 by guroux            #+#    #+#              #
#    Updated: 2019/04/19 19:33:41 by guroux           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all libft clean fclean re

NAME = ft_ls

SRC  =	src/main.c \
		src/read.c \
		src/display.c	\
		src/options.c	\
		src/sort.c		\
		src/list.c		\
		src/error.c		\

OBJECT = $(SRC:.c=.o)

HEADERS =	./includes	\

LIB = libft

CC = gcc

FLAGS = -Wall -Wextra -Werror -g

GREEN = \033[0;32m
WHITE = \033[1;37m
BLUE = \033[1;34m
RED = \033[0;31m
YELLOW = \033[1;33m

OKGREEN = $(YELLOW) $(GREEN)[OK]$(WHITE)
KORED = $(YELLOW) $(RED)[error]$(WHITE)


$(NAME): logo sign $(LIB) $(OBJECT)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJECT) -L libft/ -lft && echo "$(BLUE)Compilation$(OKGREEN)" || (echo "$(BLUE)Compilation$(KORED)" && false)

$(LIB):
	@$(MAKE) -C $(LIB)

all: $(NAME)

%.o: %.c
		@$(CC) $(FLAGS) -I $(HEADERS) -I libft/includes $< -c -o $@ && echo "$(BLUE)Objects$(OKGREEN)" || (echo "$(BLUE)Objects$(KORED)" && false)

logo:
	@echo
	@echo "                 $(GREEN)███████╗████████╗    ██╗     ███████╗"
	@echo "                 ██╔════╝╚══██╔══╝    ██║     ██╔════╝"
	@echo "                 █████╗     ██║       ██║     ███████╗"
	@echo "                 ██╔══╝     ██║       ██║     ╚════██║"
	@echo "                 ██║        ██║       ███████╗███████║"
	@echo "                 ╚═╝        ╚═╝       ╚══════╝╚══════╝"
	@echo

sign:
	@echo "██████╗ ██╗   ██╗     ██████╗ ██╗   ██╗██████╗  ██████╗ ██╗   ██╗██╗  ██╗"
	@echo "██╔══██╗╚██╗ ██╔╝    ██╔════╝ ██║   ██║██╔══██╗██╔═══██╗██║   ██║╚██╗██╔╝"
	@echo "██████╔╝ ╚████╔╝     ██║  ███╗██║   ██║██████╔╝██║   ██║██║   ██║ ╚███╔╝ "
	@echo "██╔══██╗  ╚██╔╝      ██║   ██║██║   ██║██╔══██╗██║   ██║██║   ██║ ██╔██╗ "
	@echo "██████╔╝   ██║       ╚██████╔╝╚██████╔╝██║  ██║╚██████╔╝╚██████╔╝██╔╝ ██╗"
	@echo "╚═════╝    ╚═╝        ╚═════╝  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝"
	@echo
	@echo "$(BLUE)Compilation...\n"

clean:
	@rm -rf $(OBJECT)
	@echo "$(BLUE)Deleted objects$(OKGREEN)"
	@$(MAKE) clean -C $(LIB)

fclean: clean
	@rm -rf $(NAME)
	@echo "$(BLUE)Deleted exe$(OKGREEN)"
	@$(MAKE) fclean -C $(LIB)

re: fclean all
