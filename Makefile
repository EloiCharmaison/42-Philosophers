NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC =	src/main.c \
		src/action.c \
		src/check_death.c \
		src/free.c \
		src/inits.c \
		src/time.c \
		src/utils.c \
		src/routine.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c includes/philo.h
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re