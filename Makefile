NAME = philo
CC = gcc -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -f
SRC = philosophers.c philo_utils.c\

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		$(CC) $(OBJ) -o $(NAME)

all : $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		@$(RM) $(NAME)

re: clean all

.PHONY: all fclean clean re
