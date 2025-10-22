.PHONY: all clean fclean re
NAME = libgnl.a

CFLAGS = -Wall -Wextra -Werror

SRC = get_next_line_utils.c \
	get_next_line.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

clean:
	$(RM) $(OBJ)

