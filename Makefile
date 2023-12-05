# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 12:09:59 by mkerkeni          #+#    #+#              #
#    Updated: 2023/12/05 10:16:06 by mkerkeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -g3

SRCS = 	philo.c \
		philo_utils.c \
		parsing.c \
		simulation.c \
		time.c \

OBJS = $(SRCS:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) -lpthread -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "	Compilation in progress..."
	@$(CC) $(CFLAGS) -o $(NAME) $^
	@echo "	Compiled !"

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
