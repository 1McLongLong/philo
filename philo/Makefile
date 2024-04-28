# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: touahman <touahman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 16:28:18 by touahman          #+#    #+#              #
#    Updated: 2024/04/22 16:28:39 by touahman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
CFLAGS = -Wall -Wextra -Werror

SRCF = main.c parsing.c help.c init.c routine.c check_philos.c free.c help2.c
OBJF = $(SRCF:.c=.o)
NAME = philo

all : $(NAME)

$(NAME): $(OBJF)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "🚀 Mission is complete!"

%.o : %.c header.h
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@rm -f $(OBJF)
	@echo "BYE BYE 👋"

fclean: clean
	@rm -f $(NAME)
	@echo "BYE BYE PHILO👋"

re: fclean all

.PHONY : all clean fclean re
