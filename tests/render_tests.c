#include <stdlib.h>
#include "libft.h"
#include "miniRT.h"
#include <stdio.h>
#include "parser.h"
#include "assert.h"

#ifndef LOCALPATH
# define LOCALPATH "."
#endif /* LOCALPATH */


int32_t	setupwindow(t_app *app);
void ft_put_pixel(mlx_image_t *image, int x, int y, uint32_t color);
void add_material_to_objects(t_app *app);
int32_t setupWindow(t_app *app);
void key_hook(mlx_key_data_t keydata, void *param);
void	resize_hook(int32_t width, int32_t height, void* param);
//TODO: Add function that converts the height and widht from int to string
void output_header(FILE *fptr, int32_t img_height, int32_t img_width)
{
	char	*temp;

	fputs("P3\n", fptr);
	temp = ft_itoa(img_width);
	fputs(temp, fptr);
	free(temp);
	fputs(" ", fptr);
	temp = ft_itoa(img_height);
	fputs(temp, fptr);
	free(temp);
	fputs("\n255\n", fptr);
}

void	put_pixel(FILE *fptr, t_vec3 pixel)
{
	char	*temp;

	temp = ft_itoa(pixel.x);
	fputs(temp, fptr);
	fputs(" ", fptr);
	free(temp);
	temp = ft_itoa(pixel.y);
	fputs(temp, fptr);
	fputs(" ", fptr);
	free(temp);
	temp = ft_itoa(pixel.z);
	fputs(temp, fptr);
	fputs(" ", fptr);
	free(temp);
}

int	write_pixels_to_file(FILE *fptr, mlx_image_t *img, int32_t img_height, int32_t img_width)
{
	int	x;
	int	y;
	uint8_t	*current_pixel;

	x = 0;
	y = 0;
	current_pixel = img->pixels;
	output_header(fptr, img_height, img_width);
	while (y < img_height)
	{
		while (x < img_width)
		{
			put_pixel(fptr, (t_vec3){
				.x = *current_pixel,
				.y = *(current_pixel + 1),
				.z = *(current_pixel + 2)
			});
			x++;
			current_pixel += 4;
		}
		x = 0;
		fputs("\n", fptr);
		y++;
	}
	return (0);
}

//TODO: Check and implement the render function that is called
#ifdef TEST
void draw_loop(void *args)
{
	t_app *app;

	app = (t_app *)args;
	ft_camera_render(app, ft_put_pixel, 0, app->width * app->height);
	mlx_close_window(app->mlx);
}

void	run_mlx_loop(t_app *app, char *input_f, int32_t img_height, int32_t img_width)
{
	char *argv[2];

	argv[0] = NULL;
	argv[1] = input_f;
	app->height = img_height;
	app->width = img_width;
	init_default_camera(app);
	assert(pars_init(2, argv, app) == 0 && "Failed on parsing the file");
	// print_internal_data(app);
	assert(setupwindow(app) != EXIT_FAILURE && "Failed on setting up the render window");
	mlx_loop_hook(app->mlx, draw_loop, (void *) app);
	mlx_loop(app->mlx);
}
void	run_testfile(char* file, char* output_filename, int32_t img_height, int32_t img_width)
{
	FILE	*fptr;
	t_app	app;


	printf("Testing: %s, outputting to %s\n", file, output_filename);
	run_mlx_loop(&app, file, img_height, img_width, 1);
	fptr = fopen(output_filename, "w");
	if (!fptr)
	{
		printf("File could not be opened!");
		exit(1);
	}
	write_pixels_to_file(fptr, app.image, app.height, app.width);
	fclose(fptr);
	mlx_delete_image(app.mlx, app.image);
	mlx_terminate(app.mlx);
	dyn_free(&app.hitable);
	fptr = 0;
}

int main(void)
{
	run_testfile(LOCALPATH"/tests/maps/example.rt", LOCALPATH"/tests/output/example.ppm", 400, 400);
	run_testfile(LOCALPATH"/tests/maps/complex.rt", LOCALPATH"/tests/output/complex.ppm", 800, 800);
	run_testfile(LOCALPATH"/tests/maps/complex2.rt", LOCALPATH"/tests/output/complex2.ppm", 800, 800);
	run_testfile(LOCALPATH"/tests/maps/complex3.rt", LOCALPATH"/tests/output/complex3.ppm", 800, 800);
	run_testfile(LOCALPATH"/tests/maps/cone.rt", LOCALPATH"/tests/output/cone.ppm", 800, 800);
	run_testfile(LOCALPATH"/tests/maps/glow.rt", LOCALPATH"/tests/output/glow.ppm", 800, 800);
	run_testfile(LOCALPATH"/tests/maps/spheres.rt", LOCALPATH"/tests/output/spheres.ppm", 800, 800);
	run_testfile(LOCALPATH"/tests/maps/in_plane_cube.rt", LOCALPATH"/tests/output/in_plane_cube.ppm", 800, 800);
	run_testfile(LOCALPATH"/tests/maps/box.rt", LOCALPATH"/tests/output/box.ppm", 800, 800);
	run_testfile(LOCALPATH"/tests/maps/cylinder/cylinders.rt", LOCALPATH"/tests/output/cylinders.ppm", 400, 600);
	run_testfile(LOCALPATH"/tests/maps/cylinder/cylinders_3light.rt", LOCALPATH"/tests/output/cylinders_3light.ppm", 400, 600);
	run_testfile(LOCALPATH"/tests/maps/earth.rt", LOCALPATH"/tests/output/earth.ppm", 400, 600);
}
#endif
