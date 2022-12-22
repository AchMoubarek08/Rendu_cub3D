NAME=cub3d
CC=cc
SRC=parse/errors_utils.c parse/main.c parse/map.c parse/collect.c parse/parse.c parse/parse2.c parse/parse_utils.c parse/parse_utils2.c parse/parse_utils3.c parse/./gnl/get_next_line.c parse/./gnl/get_next_line_utils.c draw.c hooks.c main.c moves.c raycast.c utils.c
OBJ=parse/errors_utils.o parse/main.o parse/map.o parse/collect.o parse/parse.o parse/parse2.o parse/parse_utils.o parse/parse_utils2.o parse/parse_utils3.o parse/./gnl/get_next_line.o parse/./gnl/get_next_line_utils.o draw.o hooks.o main.o moves.o raycast.o utils.o
SANITIZE=-fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o:%.c
	$(CC) -g -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all