.PHONY: all fclean clean re test move MLX42

# ================================ VARIABLES ================================ #
NAME        = miniRT
CC          = cc
FLAGS       = -Wall -Wextra -Werror
FLAGS_MAC   = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
FLAGS_LINUX = -ldl -lglfw -lpthread -lm
F_INC       = -Iinclude -IMLX42/include/MLX42

# ================================ LIBRARIES ================================ #
MLX         = MLX42/build/libmlx42.a
LIBFT_PATH  = ./lib/libft
LIBFT_NAME  = $(LIBFT_PATH)/libft.a
LIBGNL_PATH = ./lib/gnl
LIBGNL_NAME = $(LIBGNL_PATH)/libgnl.a
LIBRARIES   = $(LIBGNL_NAME) $(LIBFT_NAME)

# ================================ DIRECTORIES ============================== #
PARSER_DIR  = src/parser
# ================================= SOURCES ================================== #
PARSER_FILES = extract_ambient_light.c extract_camera.c extract_cordinates.c \
               extract_cylinder.c extract_light.c extract_normal.c \
               extract_plane.c extract_rgb.c extract_sphere.c parser.c \
               token_utils.c extract_triangle.c extract_cone.c token_bonus.c

FILES = src/ftray.c src/ftcolor.c src/dyn.c \
        src/ftvec3.c src/ftvec3_1.c src/ftvec3_2.c src/ftvec3_3.c \
        src/ftcamera.c src/ftcamera_2.c src/ftcamera_3.c \
        src/ft_sphere.c src/ft_cylinder.c src/ft_plane.c src/hitable.c \
        src/reflection.c src/ft_cyl_caphit.c \
        src/main.c src/pseudo_random.c src/uv.c src/texture.c \
        src/bump.c src/ft_triangle.c src/ft_cone.c src/ft_cone_cap.c \
        src/logging.c src/logging_2.c src/utils.c src/key_hooks.c

TEST_FILES       = tests/render_tests.c
FILES_WITH_TESTS = $(FILES) $(TEST_FILES)

# ============================== OS DETECTION ============================== #
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    FLAGS_OS = $(FLAGS_LINUX)
else ifeq ($(UNAME_S), Darwin)
    FLAGS_OS = $(FLAGS_MAC)
endif

# ============================= SOURCE PATHS =============================== #
PARSER_SRCS = $(addprefix $(PARSER_DIR)/, $(PARSER_FILES))
FILES      += $(PARSER_SRCS)

# ================================ TARGETS ================================== #
# all: FLAGS += -O3
all: FLAGS += -DPROD -DSTAN_SAMPLES_PER_PIXEL=5
all: $(MLX) $(LIBGNL_NAME) $(LIBFT_NAME) $(NAME)

# Run automated tests
test: FLAGS += -DTEST -DLOCALPATH=\"$(shell pwd)\"
test: fclean $(MLX) $(LIBGNL_NAME) $(LIBFT_NAME) $(FILES_WITH_TESTS:.c=.o)
	@mkdir -p tests/output
	@$(CC) $(F_INC) $(FILES_WITH_TESTS:.c=.o) -DTEST $(FLAGS) $(MLX) $(LIBRARIES) $(FLAGS_OS) -o $(NAME) && time ./miniRT && make . fclean > /dev/null

# Build with movement controls enabled
move: FLAGS += -DMOVE
move: fclean all

# ============================= BUILD RULES ================================ #
$(NAME): $(FILES:.c=.o)
	@echo "Building the executable"
	@$(CC) $(F_INC) $(FILES:.c=.o) $(FLAGS) $(MLX) $(LIBRARIES) $(FLAGS_OS) -o $(NAME)

%.o: %.c
	@echo "Building $@"
	@$(CC) -g $(F_INC) $(FLAGS) -c -o $@ $^

$(MLX):
	@cd MLX42 && cmake -B build > /dev/null && cmake --build build -j4 > /dev/null

$(LIBFT_NAME):
	@$(MAKE) -C $(LIBFT_PATH) > /dev/null

$(LIBGNL_NAME):
	@$(MAKE) -C $(LIBGNL_PATH) > /dev/null
# ============================= CLEAN RULES ================================ #
clean:
	@echo "Cleaning local objects"
	@rm -f $(FILES:.c=.o) tests/render_tests.o
	@echo "Cleaning library objects"
	@$(MAKE) -C $(LIBFT_PATH) clean > /dev/null
	@$(MAKE) -C $(LIBGNL_PATH) clean > /dev/null
	@echo "Cleaning MLX42 prebuild files"
	@rm -f MLX42/build/Makefile MLX42/build/mlx_frag_shader.c MLX42/build/mlx_vert_shader.c MLX42/build/CMakeCache.txt MLX42/build/cmake_install.cmake
	@rm -rf MLX42/build/CMakeFiles/
	@echo "\033[92mClean done!\033[0m"

fclean: clean
	@echo "Removing executable"
	@rm -f $(NAME)
	@echo "Removing MLX42 build"
	@rm -rf MLX42/build/
	@echo "Removing library builds"
	@$(MAKE) -C $(LIBFT_PATH) fclean > /dev/null
	@$(MAKE) -C $(LIBGNL_PATH) fclean > /dev/null
	@echo "\033[92mFull clean done!\033[0m"

re: fclean all
REND_TESTS	= test
