
NAME=cub3d
CC=cc
SRC=errors_utils.c main.c map.c collect.c parse.c parse2.c parse_utils.c parse_utils2.c parse_utils3.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c
OBJ=$(SRC:.c=.o)
SANITIZE=-fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -fsanitize=address -g3

%.o:%.c
	$(CC) -Wall -Wextra -Werror -g -Imlx  -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all