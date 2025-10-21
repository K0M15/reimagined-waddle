.PHONY=all fractol fclean clean re MLX42 mylibft
NAME=miniRT
CC=cc
FLAGS=-Wall -Wextra -Werror
FLAGS_MAC= -framework Cocoa -framework OpenGL -framework IOKit -lglfw
FLAGS_LINUX= -ldl -lglfw -lpthread -lm 
F_INC=-Iinclude
MLX=MLX42/build/libmlx42.a
LIBFT=libft/libft.a
FILES=src/ftray.c src/ftcolor.c src/dyn.c
FILES+=src/ftvec3.c src/ftvec3_1.c src/ftvec3_2.c src/ftvec3_3.c	# VECTOR
FILES+=src/ftcamera.c src/ftcamera_2.c								# CAMERA
FILES+=src/ft_sphere.c src/ft_cylinder.c src/ft_plane.c src/hitable.c
FILES+=src/ft_point_light.c	src/reflection.c	src/ft_cyl_caphit.c	# OBJECTS
FILES+=src/main.c src/pseudo_random.c


# all: FLAGS+=-ffast-math
# all: FLAGS+=-O3
all: $(MLX42) mylibft $(NAME)

debug: FLAGS+=-g
debug: re

MLX42:

$(NAME): $(FILES:.c=.o)
	cd MLX42 && cmake -B build && cmake --build build -j4
	$(CC) $(F_INC) $(FILES:.c=.o) $(FLAGS) $(MLX) $(LIBFT) $(FLAGS_LINUX) -o $(NAME)

%.o: %.c
	$(CC) $(F_INC) $(FLAGS) -c -o $@ $^

mylibft:
	cd ./libft && make 

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(FILES:.c=.o)

re: fclean all