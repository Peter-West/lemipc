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

NAME		=lemipc
NAME0		=display
VERSION		=0.0.1
CFLAGS		=-Wall -Werror -Wextra -g `sdl2-config --cflags`
CC 			= clang-3.5
INCLUDES	=-I libft/includes
LIB			=libft/libft.a `sdl2-config --libs`
SRC			=main.c clean.c play.c move.c turn.c sem.c shm.c msg.c signal.c \
			end.c start.c
SRC0		=sdl.c sdl_read.c
OBJ			=$(SRC:.c=.o)
OBJ0		=$(SRC0:.c=.o)

all: $(NAME) $(NAME0) finish

build:
	@($(MAKE) -C ./libft)

$(NAME): 
	$(CC) $(CFLAGS) -c $(SRC) $(INCLUDES)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

$(NAME0): 
	$(CC) $(CFLAGS) -c $(SRC0) $(INCLUDES)
	$(CC) -o $(NAME0) $(OBJ0) $(LIB)

clean:
	@(rm -rf $(OBJ))
	@(rm -rf $(OBJ0))

fclean: clean
	@(rm -rf $(NAME))
	@(rm -rf $(NAME0))

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\\\\033[32m$(NAME)\\\\033[00m]")

.PHONY: all clean fclean re v