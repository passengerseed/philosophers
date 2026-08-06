# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/10 15:54:28 by lrouchon          #+#    #+#              #
#    Updated: 2026/08/06 19:20:15 by lrouchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

NAME = philosophers

SRC_PATH = src/
SRC = $(SRC_PATH)main.c \
	$(SRC_PATH)init.c \
	$(SRC_PATH)process.c \
	$(SRC_PATH)utils.c \
	$(SRC_PATH)namegen.c \
	$(SRC_PATH)debug.c

INCLUDES = $(SRC_PATH)philosophers.h

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
