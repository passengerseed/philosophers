# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/10 15:54:28 by lrouchon          #+#    #+#              #
#    Updated: 2026/08/29 20:06:46 by lrouchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

NAME = philo

SRC = main.c \
	process.c \
	pre_process.c \
	forks.c \
	init.c \
	ft_utils_1.c \
	ft_utils_2.c \
	philo_utils.c \
	checks.c \
	exit.c

INCLUDES = philosophers.h

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
