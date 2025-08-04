#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include "minirt.h"

#define IMAGE_WIDTH_S "200"
#define IMAGE_HEIGHT_S "200"

//TODO: Add function that converts the height and widht from int to string
void output_header(FILE *fptr)
{
	fputs("P3\n", fptr);
	fputs(IMAGE_WIDTH_S, fptr);
	fputs(" ", fptr);
	fputs(IMAGE_HEIGHT_S, fptr);
	fputs("\n255\n", fptr);
}

void	put_pixel(FILE *fptr, t_rgb pixel)
{
	fputs(itoa(pixel.r), fptr);
	fputs(" ", fptr);
	fputs(itoa(pixel.g), fptr);
	fputs(" ", fptr);
	fputs(itoa(pixel.b), fptr);
	fputs(" ", fptr);
}

int	write_pixels_to_file(FILE *fptr)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	output_header(fptr);
	while (y < IMAGE_HEIGHT)
	{
		while (x < IMAGE_WIDTH)
		{
			put_pixel(fptr, get_scene()->pixels[y][x]);
			x++;
		}
		x = 0;
		fputs("\n", fptr);
		y++;
	}
	return (0);
}

//TODO: Check and implement the render function that is called
int main(void)
{
	FILE *fptr;
	const char *input_f = "./tests/maps/example.rt"

	fptr = fopen("image.ppm", "w");
	if (!fptr)
	{
		printf("File could not be opened!");
		exit(1);
	}
	render(input_f);
	write_pixels_to_file(fptr);
	fclose(fptr);
	fptr = 0;
}
