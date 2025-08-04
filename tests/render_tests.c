#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include "minirt.h"
#include "libft.h"

//TODO: Add function that converts the height and widht from int to string
void output_header(FILE *fptr)
{
	char	*temp;

	fputs("P3\n", fptr);
	temp = ft_itoa(IMAGE_WIDTH);
	fputs(temp, fptr);
	free(temp);
	fputs(" ", fptr);
	temp = ft_itoa(IMAGE_HEIGHT);
	fputs(temp, fptr);
	free(temp);
	fputs("\n255\n", fptr);
}

void	put_pixel(FILE *fptr, t_rgb pixel)
{
	char	*temp;

	temp = ft_itoa(pixel.r);
	fputs(temp, fptr);
	fputs(" ", fptr);
	free(temp);
	temp = ft_itoa(pixel.g);
	fputs(temp, fptr);
	fputs(" ", fptr);
	free(temp);
	temp = ft_itoa(pixel.r);
	fputs(temp, fptr);
	fputs(" ", fptr);
	free(temp);
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
	const char *input_f = "./tests/maps/example.rt";

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
