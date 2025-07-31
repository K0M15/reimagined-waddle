#TODO: Still have to compile libft
NAME        = miniRT 
UN_TESTS	= test
CC          = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude


LIBFT_PATH  = ./lib/libft
LIBFT_NAME	= ft
GNL_PATH    = ./lib/gnl

LIBRARIES   = -L$(LIBFT_PATH) -l$(LIBFT_NAME)

UN_TESTS_DIR	=	tests/unit_test

UN_TEST_FILES	=	main.c \
					vec3_test.c \
					parser_test.c


UN_TEST_SRCS = $(addprefix $(UN_TESTS_DIR)/, $(UN_TEST_FILES))

VEC3_DIR	=	src/math
PARSER_DIR	=	src/parser
SCENE_DIR	=	src

VEC3_FILES	=	vec3_add_sub.c \
				vec3_copy_dup.c \
				vec3_debug.c \
				vec3_dot_cross_prod.c \
				vec3_length_multiply.c \
				vec3_mult_sub_const.c \
				vec3_negate_unitv.c

VEC3_SRCS	+= $(addprefix $(VEC3_DIR)/, $(VEC3_FILES))

PARSER_FILES 	=	extract_rgb.c \
			token_utils.c \
			extract_ambient_light.c

PARSER_SRCS	+= $(addprefix $(PARSER_DIR)/, $(PARSER_FILES))

SCENE_FILES	=	scene_utils.c

SCENE_SRCS	+= $(addprefix $(SCENE_DIR)/, $(SCENE_FILES))

UN_TEST_SRCS += $(VEC3_SRCS) $(PARSER_SRCS) $(SCENE_SRCS)
SRCS = $(VEC3_SRCS) $(PARSER_SRCS) $(SCENE_SRCS)

UN_TEST_OBJS = $(UN_TEST_SRCS:.c=.o)
OBJS        = $(SRCS:.c=.o)


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) > /dev/null
	@echo "\033[1;32m✔ Compiled: $<\033[0m"

$(NAME): $(OBJS)
	@$(CC) -g -fsanitize=address $(OBJS) $(LIBRARIES) -o $(NAME) > /dev/null
#	@$(CC) -g $(OBJS) $(LIBRARIES) -o $(NAME) > /dev/null

$(UN_TESTS): $(UN_TEST_OBJS)
	@$(MAKE) -C ./lib/libft > /dev/null
	@$(CC) -g -fsanitize=address $(UN_TEST_OBJS) $(LIBRARIES) -o $(UN_TESTS) > /dev/null
#	@$(CC) -g $(UN_TEST_OBJS) $(LIBRARIES) -o $(UN_TESTS) > /dev/null

clean:
	@rm -f $(OBJS) > /dev/null

unclean:
	@$(MAKE) -C ./lib/libft clean > /dev/null
	@rm -f $(UN_TEST_OBJS) > /dev/null

fclean: clean
	@rm -f $(NAME) > /dev/null
	@echo "\033[1;33m Fully cleaned $(NAME)!\033[0m"

unfclean: unclean
	@$(MAKE) -C ./lib/libft fclean > /dev/null
	@rm -f $(UN_TESTS) > /dev/null
	@echo "\033[1;33m Fully cleaned $(UN_TESTS)!\033[0m"

re: fclean all

unre: unfclean $(UN_TESTS)

all: $(NAME)

.PHONY: all clean fclean re unclean unfclean unre
