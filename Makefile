#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/26 19:04:30 by ppellegr          #+#    #+#              #
#    Updated: 2015/03/26 19:04:31 by ppellegr         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME=lemipc
VERSION=0.0.1
CFLAGS=-Wall -Werror -Wextra -g
CC = clang-3.5
# CC = gcc
INCLUDES=-I libft/includes
LIB=libft/libft.a
SRC=main.c clean.c play.c move.c turn.c sem.c shm.c msg.c signal.c end.c \
start.c
OBJ=$(SRC:.c=.o)

all: $(NAME) finish

build:
	@($(MAKE) -C ./libft)

$(NAME): 
	$(CC) $(CFLAGS) -c $(SRC) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

clean:
	@(rm -rf $(OBJ))

fclean: clean
	@(rm -rf $(NAME))

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\\\\033[32m$(NAME)\\\\033[00m]")

.PHONY: all clean fclean re v