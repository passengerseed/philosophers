# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/10 15:54:28 by lrouchon          #+#    #+#              #
#    Updated: 2026/05/10 15:55:08 by lrouchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

LFLAGS =

NAME = philosophers

SRC_PATH = src/
SRC = $(SRC_PATH)main.c \

LIBS = libft/libft.a \

INCLUDES = $(SRC_PATH)philosophers.h

OBJ = $(SRC:.c=.o)

all: libs $(NAME)

libs :
	make -C libft/

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) $(LIBS) -o $(NAME) -lm

clean:
	rm -f $(OBJ)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: all clean fclean re
