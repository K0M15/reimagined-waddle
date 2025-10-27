.PHONY: all fractol fclean clean re MLX42
NAME=miniRT
CC=cc
FLAGS=-Wall -Wextra -Werror
FLAGS_MAC= -framework Cocoa -framework OpenGL -framework IOKit -lglfw
FLAGS_LINUX= -ldl -lglfw -lpthread -lm 
F_INC=-Iinclude
MLX=MLX42/build/libmlx42.a
PARSER_DIR	=	src/parser
SCENE_DIR	=	src
LIBFT_PATH  = ./lib/libft
LIBFT_NAME  = $(LIBFT_PATH)/libft.a
LIBGNL_PATH    = ./lib/gnl
LIBGNL_NAME	= $(LIBGNL_PATH)/libgnl.a
PARSER_FILES 	=	extract_ambient_light.c \
			extract_camera.c \
			extract_cordinates.c \
			extract_cylinder.c \
			extract_light.c \
			extract_normal.c \
			extract_plane.c \
			extract_rgb.c \
			extract_sphere.c \
			parser.c \
			token_utils.c
FILES=src/ftray.c src/ftcolor.c src/dyn.c
FILES+=src/ftvec3.c src/ftvec3_1.c src/ftvec3_2.c src/ftvec3_3.c	# VECTOR
FILES+=src/ftcamera.c src/ftcamera_2.c								# CAMERA
FILES+=src/ft_sphere.c src/ft_cylinder.c src/ft_plane.c src/hitable.c
FILES+=src/ft_point_light.c	src/reflection.c	src/ft_cyl_caphit.c	# OBJECTS
FILES+=src/main.c src/pseudo_random.c
TEST_FILES=tests/render_tests.c
FILES_WITH_TESTS+=$(FILES) $(TEST_FILES)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    FLAGS_OS = $(FLAGS_LINUX)
else ifeq ($(UNAME_S), Darwin)
    FLAGS_OS = $(FLAGS_MAC)
endif

SCENE_FILES	=	scene_utils.c
SCENE_SRCS	+= $(addprefix $(SCENE_DIR)/, $(SCENE_FILES))
PARSER_SRCS	+= $(addprefix $(PARSER_DIR)/, $(PARSER_FILES))
FILES+=$(PARSER_SRCS)
LIBRARIES   = $(LIBGNL_NAME) $(LIBFT_NAME)

# all: FLAGS+=-ffast-math
# all: FLAGS+=-O3
all: $(MLX) $(LIBGNL_NAME) $(LIBFT_NAME) $(NAME)

debug: FLAGS+=-g
debug: re


test: $(MLX) $(LIBGNL_NAME) $(LIBFT_NAME) $(FILES_WITH_TESTS:.c=.o)
	$(CC) $(F_INC) $(FILES_WITH_TESTS:.c=.o) -DTEST $(FLAGS) $(MLX) $(LIBRARIES) $(FLAGS_LINUX) -o $(NAME)

$(MLX):
	cd MLX42 && cmake -B build && cmake --build build -j4

$(NAME): $(FILES:.c=.o)
	$(CC) $(F_INC) $(FILES:.c=.o) $(FLAGS) $(MLX) $(LIBRARIES) $(FLAGS_LINUX) -o $(NAME)

%.o: %.c
	@echo "Building $@"
	@$(CC) -g -DTEST $(F_INC) $(FLAGS) -c -o $@ $^



$(LIBFT_NAME):
	@$(MAKE) -C $(LIBFT_PATH) > /dev/null

$(LIBGNL_NAME):
	@$(MAKE) -C $(LIBGNL_PATH) > /dev/null

fclean: clean
	@echo "Removing executeable"
	@rm -f $(NAME)
	@echo "Removing MLX42 build"
	@rm -rf MLX42/build/
	@echo "Removing Libft build"
	@make -C $(LIBFT_PATH) fclean > /dev/null
	@make -C $(LIBGNL_PATH) fclean > /dev/null
	@echo "\033[92mRemoving done!\033[0m"

clean:
	@echo "Clean local objects"
	@rm -f $(FILES:.c=.o)
	@echo "Clean libft objects"
	@make -C $(LIBFT_PATH) clean > /dev/null
	@make -C $(LIBGNL_PATH) clean > /dev/null
	@echo "Clean MLX42 prebuild files"
	@rm -f MLX42/build/Makefile MLX42/build/mlx_frag_shader.c MLX42/build/mlx_vert_shader.c MLX42/build/CMakeCache.txt MLX42/build/cmake_install.cmake
	@rm -rf MLX42/build/CMakeFiles/
	@echo "\033[92mClean done!\033[0m"

re: fclean all
#NAME        = miniRT 
UN_TESTS	= untest
REND_TESTS	= test
#CC          = cc
#CFLAGS = -Wall -Wextra -Werror -Iinclude
#
#
#LIBFT_PATH  = ./lib/libft
#LIBFT_NAME	= ft
#
#REND_DIR	=	src/renderer
#
#
#
#
#UN_TEST_DIR	=	tests/unit_test
#
#UN_TEST_FILES	=	main.c \
#			vec3_test.c \
#			parser_test.c \
#			whole_parser_test.c
#
#REND_TEST_DIR	=	tests
#
#REND_TEST_FILES=	render_tests.c
#
#UN_TEST_SRCS = $(addprefix $(UN_TEST_DIR)/, $(UN_TEST_FILES))
#REND_TEST_SRCS	= $(addprefix $(REND_TEST_DIR)/, $(REND_TEST_FILES))
#

#REND_FILES	=	 render.c \
#			ray_calc.c
#
#REND_SRCS	+= $(addprefix $(REND_DIR)/, $(REND_FILES))
#
#UN_TEST_SRCS += $(PARSER_SRCS) $(SCENE_SRCS)
#SRCS = $(PARSER_SRCS) $(SCENE_SRCS) $(REND_SRCS)
#REND_TEST_SRCS	+= $(PARSER_SRCS) $(SCENE_SRCS) $(REND_SRCS)
#
#UN_TEST_OBJS = $(UN_TEST_SRCS:.c=.o)
#OBJS        = $(SRCS:.c=.o)
#REND_TEST_OBJS = $(REND_TEST_SRCS:.c=.o)
#
#compile_libs:
#	@$(MAKE) -C $(LIBFT_PATH) > /dev/null

#	@echo "\033[1;32m✔ Compiled: LIBS\033[0m"
#
#remote_libs:
#	@$(MAKE) -C $(LIBFT_PATH) fclean > /dev/null
#	@$(MAKE) -C $(LIBGNL_PATH) fclean > /dev/null
#	@$(MAKE) -C $(LIBLLIST_PATH) fclean > /dev/null
#	@echo "\033[1;33m✔ Removed: LIBS\033[0m"
#	
#%.o: %.c
#	@$(CC) -g $(CFLAGS) -c $< -o $@ $(INCLUDES) > /dev/null
#	@echo "\033[1;32m✔ Compiled: $<\033[0m"
#
#$(NAME): $(OBJS) compile_libs
#	@$(CC) -g -fsanitize=address $(OBJS) $(LIBRARIES) -o $(NAME) > /dev/null
##	@$(CC) -g $(OBJS) $(LIBRARIES) -o $(NAME) > /dev/null
#
#$(UN_TESTS): $(UN_TEST_OBJS) compile_libs
#	@$(CC) -g -fsanitize=address $(UN_TEST_OBJS) $(LIBRARIES) -o $(UN_TESTS) > /dev/null
##	@$(CC) -g $(UN_TEST_OBJS) $(LIBRARIES) -o $(UN_TESTS) > /dev/null
#
#$(REND_TESTS): $(REND_TEST_OBJS) compile_libs
#	@$(CC) -g -fsanitize=address $(REND_TEST_OBJS) $(LIBRARIES) -o $(REND_TESTS) > /dev/null
##	@$(CC) -g $(REND_TEST_OBJS) $(LIBRARIES) -o $(REND_TESTS) > /dev/null
#
#clean: remote_libs
#	@rm -f $(OBJS) > /dev/null
#
#unclean: remote_libs
#	@$(MAKE) -C ./lib/libft fclean > /dev/null
#	@rm -f $(UN_TEST_OBJS) > /dev/null
#
#rdclean: remote_libs
#	@$(MAKE) -C ./lib/libft fclean > /dev/null
#	@rm -f $(REND_TEST_OBJS) > /dev/null
#
#fclean: clean
#	@rm -f $(NAME) > /dev/null
#	@echo "\033[1;33m Fully cleaned $(NAME)!\033[0m"
#
#unfclean: unclean
#	@$(MAKE) -C ./lib/libft fclean > /dev/null
#	@rm -f $(UN_TESTS) > /dev/null
#	@echo "\033[1;33m Fully cleaned $(UN_TESTS)!\033[0m"
#
#rdfclean: rdclean
#	@$(MAKE) -C ./lib/libft fclean > /dev/null
#	@rm -f $(REND_TESTS) > /dev/null
#	@echo "\033[1;33m Fully cleaned $(REND_TESTS)!\033[0m"
#
#re: fclean all
#
#unre: unfclean $(UN_TESTS)
#
#rdre: rdfclean $(REND_TESTS)
#
#all: $(NAME)
#
#.PHONY: all clean fclean re unclean unfclean unre rdclean rdfclean rdre
#>>>>>>> rt_temp/temp
