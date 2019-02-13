# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guroux <guroux@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/31 17:49:13 by guroux            #+#    #+#              #
#    Updated: 2019/02/13 19:26:52 by guroux           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all libft clean fclean re

NAME = ft_ls

SRC  =	src/main.c \
		src/read.c \
		src/display.c	\
		src/options.c	\
		src/sort.c

OBJECT = $(SRC:.c=.o)

HEADERS =	./includes	\

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
	@echo "$(YELLOW)          _____  $(BLUE)              _____    $(RED)                        _____     $(GREEN)       _____          "
	@echo "$(YELLOW)         /\    \ $(BLUE)             /\    \    $(RED)                      /\    \   $(GREEN)       /\    \         "
	@echo "$(YELLOW)        /::\    \ $(BLUE)           /::\    \   $(RED)                     /::\____\  $(GREEN)      /::\    \        "
	@echo "$(YELLOW)       /::::\    \  $(BLUE)         \:::\    \   $(RED)                   /:::/    /  $(GREEN)     /::::\    \       "
	@echo "$(YELLOW)      /::::::\    \   $(BLUE)        \:::\    \  $(RED)                  /:::/    /   $(GREEN)    /::::::\    \      "
	@echo "$(YELLOW)     /:::/\:::\    \   $(BLUE)        \:::\    \  $(RED)                /:::/    /   $(GREEN)    /:::/\:::\    \     "
	@echo "$(YELLOW)    /:::/__\:::\    \  $(BLUE)         \:::\    \  $(RED)              /:::/    /    $(GREEN)   /:::/__\:::\    \    "
	@echo "$(YELLOW)   /::::\   \:::\    \   $(BLUE)       /::::\    \  $(RED)            /:::/    /     $(GREEN)   \:::\   \:::\    \   "
	@echo "$(YELLOW)  /::::::\   \:::\    \  $(BLUE)      /::::::\    \   $(RED)         /:::/    /     $(GREEN)  ___\:::\   \:::\    \  "
	@echo "$(YELLOW) /:::/\:::\   \:::\    \  $(BLUE)    /:::/\:::\    \   $(RED)       /:::/    /     $(GREEN)  /\   \:::\   \:::\    \ "
	@echo "$(YELLOW)/:::/  \:::\   \:::\____\  $(BLUE)  /:::/  \:::\____\  $(RED)      /:::/____/     $(GREEN)  /::\   \:::\   \:::\____\\"
	@echo "$(YELLOW)\::/    \:::\   \::/    /  $(BLUE) /:::/    \::/    /  $(RED)      \:::\    \    $(GREEN)   \:::\   \:::\   \::/    /"
	@echo "$(YELLOW) \/____/ \:::\   \/____/ $(BLUE)  /:::/    / \/____/   $(RED)       \:::\    \   $(GREEN)    \:::\   \:::\   \/____/ "
	@echo "$(YELLOW)          \:::\    \   $(BLUE)   /:::/    /            $(RED)        \:::\    \  $(GREEN)     \:::\   \:::\    \     "
	@echo "$(YELLOW)           \:::\____\  $(BLUE)  /:::/    /            $(RED)          \:::\    \  $(GREEN)     \:::\   \:::\____\    "
	@echo "$(YELLOW)            \::/    /  $(BLUE)  \::/    /            $(RED)            \:::\    \  $(GREEN)     \:::\  /:::/    /    "
	@echo "$(YELLOW)             \/____/   $(BLUE)   \/____/            $(RED)              \:::\    \   $(GREEN)    \:::\/:::/    /     "
	@echo "$(YELLOW)                       $(BLUE)                      $(RED)               \:::\    \  $(GREEN)     \::::::/    /      "
	@echo "$(YELLOW)                       $(BLUE)                      $(RED)                \:::\____\  $(GREEN)     \::::/    /       "
	@echo "$(YELLOW)                       $(BLUE)                      $(RED)                 \::/    /   $(GREEN)     \::/    /        "
	@echo "$(YELLOW)                       $(BLUE)                      $(RED)                  \/____/    $(GREEN)      \/____/         "
	@echo "$(YELLOW)                       $(BLUE)                      $(RED)                            $(GREEN)                       "
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
