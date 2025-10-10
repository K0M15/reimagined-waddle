.PHONY: all clean fclean re
NAME = libllist.a

CFLAGS = -Wall -Wextra -Werror

SRC = ft_ll_add_node.c \
	ft_ll_delete_node.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

clean:
	$(RM) $(OBJ)

