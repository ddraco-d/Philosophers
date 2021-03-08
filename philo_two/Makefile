# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddraco <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/07 19:56:09 by ddraco            #+#    #+#              #
#    Updated: 2021/03/08 12:23:01 by ddraco           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two

SRC = eat.c init.c main.c threads_begin.c utils.c utils1.c

OBJ = $(SRC:.c=.o)

HEADER = philo.h

FLAGS = -Wall -Werror -Wextra -I./includes

all: $(NAME)

$(NAME):$(OBJ)
	cc -o $(NAME) $(FLAGS) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re