# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 11:37:05 by fmaurer           #+#    #+#              #
#    Updated: 2024/09/19 13:38:43 by fmaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minitalk

CC			= cc

CFLAGS	= -Wall -Wextra -Werror

LIBFT_PATH	= ./libft
LIBFT				= $(LIBFT_PATH)/libft.a

SRC_FILES_SRV =	./server.c ./miniutils.c
SRC_FILES_CLI =	./client.c ./miniutils.c
SRC_FILES_CLI_BONUS  =	./client_bonus.c ./miniutils.c ./utils_bonus.c

SRC_SRV = $(patsubst ./%.c,%.c,$(SRC_FILES_SRV))
SRC_CLI = $(patsubst ./%.c,%.c,$(SRC_FILES_CLI))
SRC_CLI_BONUS = $(patsubst ./%.c,%.c,$(SRC_FILES_CLI_BONUS))

all: $(NAME)

$(NAME): server client

server: $(SRC_SRV) | $(LIBFT)
	cc $(CFLAGS) -o server $(SRC_SRV) $(LIBFT)

client: $(SRC_CLI) | $(LIBFT)
	cc $(CFLAGS) -o client $(SRC_CLI) $(LIBFT)

client_bonus: $(SRC_CLI_BONUS) | $(LIBFT)
	cc $(CFLAGS) -o client_bonus $(SRC_CLI_BONUS) $(LIBFT)

bonus: server client_bonus

bonus: server client_bonus.c
	cc -g $(CFLAGS) -o client_bonus $(SRC_CLI_BONUS) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_PATH) all

clean: fclean

fclean:
	@make -s -C $(LIBFT_PATH) fclean
	@echo "Removing $(NAME) binaries..."
	@rm -f server client client_bonus

re: fclean all

.PHONY: all clean fclean re bonus
