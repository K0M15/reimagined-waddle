.PHONY=all fractol fclean clean re MLX42 FT_PRINTF
NAME=miniRT
CC=cc
FLAGS=-Wall -Wextra -Werror
FLAGS_MAC= -framework Cocoa -framework OpenGL -framework IOKit -lglfw
FLAGS_LINUX= -ldl -lglfw -lpthread -lm 
F_INC=-Iinclude
MLX=MLX42/build/libmlx42.a
FILES=src/ftray.c src/ftvec3.c src/ftcamera.c src/dyn.c
FILES+=src/main.c


all: FLAGS+=-ffast-math
all: FLAGS+=-O3
all: MLX42 $(NAME)

MLX42:
	@if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B build && cmake --build build -j4

debug: FLAGS+=-g
debug: re

$(NAME): $(FILES:.c=.o)
	$(CC) $(F_INC) $(FILES:.c=.o) $(FLAGS) $(MLX) $(FLAGS_MAC) -o $(NAME)

%.o: %.c
	$(CC) $(F_INC) $(FLAGS) -c -o $@ $^

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(FILES:.c=.o)

re: fclean all