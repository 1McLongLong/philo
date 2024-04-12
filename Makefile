CC = cc 
CFLAGS = #-Wall -Wextra -Werror #-pthread -fsanitize=thread

SRCF = $(addprefix src/, main.c check_philo.c free.c help.c init.c parsing.c routine.c)
OBJF = $(SRCF:.c=.o)
NAME = philo

all : $(NAME)

$(NAME): $(OBJF)
	@$(CC) $(CFLAGS) $^ -o $@ $(READLINE_LIB)
	@echo "🚀 Mission is complete!"

%.o : %.c ./src/header.h
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@rm -f $(OBJF)
	@echo "BYE BYE 👋"

fclean: clean
	@rm -f $(NAME)
	@echo "BYE BYE PHILO👋"

re: fclean all

.PHONY : all clean fclean re
