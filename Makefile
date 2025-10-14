.PHONY: all fractol fclean clean re MLX42 mylibft
NAME=miniRT
CC=cc
FLAGS=-Wall -Wextra -Werror
FLAGS_MAC= -framework Cocoa -framework OpenGL -framework IOKit -lglfw
FLAGS_LINUX= -ldl -lglfw -lpthread -lm 
F_INC=-Iinclude
MLX=MLX42/build/libmlx42.a
LIBFT=libft/libft.a
FILES=src/ftray.c src/ftvec3.c src/ftcamera.c src/dyn.c
FILES+=src/main.c src/pseudo_random.c

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    FLAGS_OS = $(FLAGS_LINUX)
else ifeq ($(UNAME_S), Darwin)
    FLAGS_OS = $(FLAGS_MAC)
endif

all: FLAGS+=-ffast-math
all: FLAGS+=-O3
all: $(LIBFT) $(MLX) $(NAME)

$(MLX):
	cd MLX42 && cmake -B build && cmake --build build -j4

debug: FLAGS+=-g
debug: re

$(NAME): $(FILES:.c=.o)
	@$(CC) $(F_INC) $(FILES:.c=.o) $(FLAGS) $(MLX) $(LIBFT) $(FLAGS_OS) -o $(NAME)
	@echo "\033[92mBuilt executeable $@ finished!\033[0m"

%.o: %.c
	@echo "Building $@"
	@$(CC) $(F_INC) $(FLAGS) -c -o $@ $^

$(LIBFT):
	cd ./libft && make 

fclean: clean
	@echo "Removing executeable"
	@rm -f $(NAME)
	@echo "Removing MLX42 build"
	@rm -rf MLX42/build/
	@echo "Removing Libft build"
	@cd ./libft && make clean
	@echo "\033[92mRemoving done!\033[0m"

clean:
	@echo "Clean local objects"
	@rm -f $(FILES:.c=.o)
	@echo "Clean libft objects"
	@cd ./libft && make clean
	@echo "Clean MLX42 prebuild files"
	@rm -f MLX42/build/Makefile MLX42/build/mlx_frag_shader.c MLX42/build/mlx_vert_shader.c MLX42/build/CMakeCache.txt MLX42/build/cmake_install.cmake
	@rm -rf MLX42/build/CMakeFiles/
	@echo "\033[92mClean done!\033[0m"

re: fclean all