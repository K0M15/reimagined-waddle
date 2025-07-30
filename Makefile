NAME        = miniRT 
UN_TESTS	= test
CC          = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude


LIBFT_PATH  = ./lib/libft
GNL_PATH    = ./lib/gnl

LIBRARIES   =  

UN_TESTS_DIR	=	tests/unit_test

UN_TEST_FILES	=	main.c \
					vec3_test.c

UN_TEST_SRCS = $(addprefix $(UN_TESTS_DIR)/, $(UN_TEST_FILES))

VEC3_DIR	=	src/math

VEC3_FILES	=	vec3_add_sub.c \
				vec3_copy_dup.c \
				vec3_debug.c \
				vec3_dot_cross_prod.c \
				vec3_length_multiply.c \
				vec3_mult_sub_const.c \
				vec3_negate_unitv.c

VEC3_SRCS	+= $(addprefix $(VEC3_DIR)/, $(VEC3_FILES))

UN_TEST_SRCS += $(VEC3_SRCS)
SRCS = $(VEC3_SRCS)

UN_TEST_OBJS = $(UN_TEST_SRCS:.c=.o)
OBJS        = $(SRCS:.c=.o)


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) > /dev/null
	@echo "\033[1;32m✔ Compiled: $<\033[0m"

$(NAME): $(OBJS)
	@$(CC) -g -fsanitize=address $(OBJS) $(LIBRARIES) -o $(NAME) > /dev/null

$(UN_TESTS): $(UN_TEST_OBJS)
	@$(CC) -g -fsanitize=address $(UN_TEST_OBJS) $(LIBRARIES) -o $(UN_TESTS) > /dev/null

clean:
	@rm -f $(OBJS) > /dev/null

unclean:
	@rm -f $(UN_TEST_OBJS) > /dev/null

fclean: clean
	@rm -f $(NAME) > /dev/null
	@echo "\033[1;33m Fully cleaned $(NAME)!\033[0m"

unfclean: unclean
	@rm -f $(UN_TESTS) > /dev/null
	@echo "\033[1;33m Fully cleaned $(UN_TESTS)!\033[0m"

re: fclean all

unre: unfclean $(UN_TESTS)

all: $(NAME)

.PHONY: all clean fclean re unclean unfclean unre
