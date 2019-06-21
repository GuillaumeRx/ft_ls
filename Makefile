# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guroux <guroux@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/31 17:49:13 by guroux            #+#    #+#              #
#    Updated: 2019/06/21 16:32:59 by guroux           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all libft clean fclean re

NAME = ft_ls

SRC  =	src/main.c \
		src/read.c \
		src/long_read.c \
		src/display.c \
		src/display_long.c \
		src/display_long_2.c \
		src/misc.c \
		src/options.c \
		src/sort.c \
		src/list.c \
		src/error.c \
		src/dir_parsing.c \

OBJECT = $(SRC:.c=.o)

HEADERS =	./includes

LIB = libft

CC = gcc

FLAGS = -Wall -Wextra -Werror

GREEN = \033[0;32m
WHITE = \033[1;37m
BLUE = \033[1;34m
RED = \033[0;31m
YELLOW = \033[1;33m

OKGREEN = $(YELLOW) $(GREEN)[OK]$(WHITE)
KORED = $(YELLOW) $(RED)[error]$(WHITE)


$(NAME): logo $(LIB) $(OBJECT)
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
