# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 11:37:05 by fmaurer           #+#    #+#              #
#    Updated: 2024/09/04 14:36:39 by fmaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minitalk

CC			= cc

CFLAGS	= -Wall -Wextra -Werror

LIBFT_PATH	= ./libft
LIBFT				= $(LIBFT_PATH)/libft.a

SRC_FILES_SRV =	./server.c ./miniutils.c
SRC_FILES_CLI =	./client.c ./miniutils.c

SRC_SRV = $(patsubst ./%.c,%.c,$(SRC_FILES_SRV))
SRC_CLI = $(patsubst ./%.c,%.c,$(SRC_FILES_CLI))

all: $(NAME)

$(NAME): server client

server: $(SRC_SRV) | $(LIBFT)
	cc -g $(CFLAGS) -o server $(SRC_SRV) $(LIBFT)

client: $(SRC_CLI) | $(LIBFT)
	cc -g $(CFLAGS) -o client $(SRC_CLI) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_PATH) all

clean: fclean

fclean:
	@make -s -C $(LIBFT_PATH) fclean
	@echo "Removing $(NAME) binaries..."
	@rm -f server client

re: fclean all

.PHONY: all clean fclean re
