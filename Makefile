NAME        = miniRT 
UN_TESTS	= test
CC          = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude


LIBFT_PATH  = ./lib/libft
LIBFT_NAME	= ft
LIBGNL_PATH    = ./lib/gnl
LIBGNL_NAME	= gnl 
LIBLLIST_PATH  = ./lib/llist
LIBLLIST_NAME	= llist

LIBRARIES   = -L$(LIBFT_PATH) -l$(LIBFT_NAME) -L$(LIBGNL_PATH) -l$(LIBGNL_NAME) -L$(LIBLLIST_PATH) -l$(LIBLLIST_NAME)

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
			extract_normal.c \
			extract_cordinates.c \
			token_utils.c \
			extract_ambient_light.c \
			extract_camera.c \
			extract_light.c

PARSER_SRCS	+= $(addprefix $(PARSER_DIR)/, $(PARSER_FILES))

SCENE_FILES	=	scene_utils.c

SCENE_SRCS	+= $(addprefix $(SCENE_DIR)/, $(SCENE_FILES))

UN_TEST_SRCS += $(VEC3_SRCS) $(PARSER_SRCS) $(SCENE_SRCS)
SRCS = $(VEC3_SRCS) $(PARSER_SRCS) $(SCENE_SRCS)

UN_TEST_OBJS = $(UN_TEST_SRCS:.c=.o)
OBJS        = $(SRCS:.c=.o)

compile_libs:
	@$(MAKE) -C $(LIBFT_PATH) > /dev/null
	@$(MAKE) -C $(LIBGNL_PATH) > /dev/null
	@$(MAKE) -C $(LIBLLIST_PATH) > /dev/null
	@echo "\033[1;32m✔ Compiled: LIBS\033[0m"

remote_libs:
	@$(MAKE) -C $(LIBFT_PATH) fclean > /dev/null
	@$(MAKE) -C $(LIBGNL_PATH) fclean > /dev/null
	@$(MAKE) -C $(LIBLLIST_PATH) fclean > /dev/null
	@echo "\033[1;33m✔ Removed: LIBS\033[0m"
	

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) > /dev/null
	@echo "\033[1;32m✔ Compiled: $<\033[0m"

$(NAME): $(OBJS) compile_libs
	@$(CC) -g -fsanitize=address $(OBJS) $(LIBRARIES) -o $(NAME) > /dev/null
#	@$(CC) -g $(OBJS) $(LIBRARIES) -o $(NAME) > /dev/null

$(UN_TESTS): $(UN_TEST_OBJS) compile_libs
	@$(CC) -g -fsanitize=address $(UN_TEST_OBJS) $(LIBRARIES) -o $(UN_TESTS) > /dev/null
#	@$(CC) -g $(UN_TEST_OBJS) $(LIBRARIES) -o $(UN_TESTS) > /dev/null

clean: remote_libs
	@rm -f $(OBJS) > /dev/null

unclean: remote_libs
	@$(MAKE) -C ./lib/libft fclean > /dev/null
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
