NAME        = tests 
CC          = cc
CFLAGS = -Wall -Wextra -Werror -I../../include


LIBFT_PATH  = ./lib/libft
PRINTF_PATH = ./lib/ft_printf
GNL_PATH    = ./lib/gnl

LIBRARIES   =  


SRCS		=	main.c \
				vec3_test.c

VEC3_DIR	=	../../src/math

VEC3_SRCS 	=	vec3_add_sub.c \
				vec3_copy_dup.c \
				vec3_debug.c \
				vec3_dot_cross_prod.c \
				vec3_length_multiply.c \
				vec3_mult_sub_const.c \
				vec3_negate_unitv.c

SRCS += $(addprefix $(VEC3_DIR)/, $(VEC3_SRCS))

OBJS        = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) > /dev/null
	@echo "\033[1;32m✔ Compiled: $<\033[0m"

$(NAME): $(OBJS)
	@$(CC) -g -fsanitize=address $(OBJS) $(LIBRARIES) -o $(NAME) > /dev/null

clean:
	@rm -f $(OBJS) > /dev/null

fclean: clean
	@rm -f $(NAME) > /dev/null
	@echo "\033[1;33m Fully cleaned $(NAME)!\033[0m"

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re
