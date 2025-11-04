#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "miniRT.h"

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
			put_pixel(fptr, (t_vec3){.x = *current_pixel, .y = *(current_pixel + 1), .z = *(current_pixel + 2)});
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
	t_camera camera;

	app->width = img_width;
	app->height = img_height;
	ft_camera_init(
		&camera, (t_camera_p){
			ftvec3(0),
			(t_vec3){0,0, -1},
			90,
			app->width,
			app->height,
			STAN_SAMPLES_PER_PIXEL,
			(t_vec3){
				1, 1, 1
			},
			.2,
			1000.0f
		});
	app->active_camera = camera;
	if (pars_init(2, (char*[]){"./miniRT", input_f, "\0"}, app) != 0)
		return ;
	ft_camera_calc(&app->active_camera);
	add_material_to_objects(app);
	if (setupWindow(app) == EXIT_FAILURE)
		return ;	
	
	mlx_key_hook(app->mlx, key_hook, (void *) app);
	mlx_loop_hook(app->mlx, draw_loop, (void *) app);
  	mlx_resize_hook(app->mlx, resize_hook, (void *) app);
	mlx_loop(app->mlx);
}
void	run_testfile(char* file, char* output_filename, int32_t img_height, int32_t img_width)
{
	FILE	*fptr;
	t_app	app;

	run_mlx_loop(&app, file, img_height, img_width);
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
	run_testfile("./tests/maps/example.rt", "example.ppm", 400, 400);
	run_testfile("./tests/maps/complex.rt", "complex.ppm", 800, 800);
	run_testfile("./tests/maps/complex2.rt", "complex2.ppm", 800, 800);
	run_testfile("./tests/maps/complex3.rt", "complex3.ppm", 800, 800);
	run_testfile("./tests/maps/cone.rt", "cone.ppm", 800, 800);
	run_testfile("./tests/maps/glow.rt", "glow.ppm", 800, 800);
	run_testfile("./tests/maps/spheres.rt", "spheres.ppm", 800, 800);
	run_testfile("./tests/maps/in_plane_cube.rt", "in_plane_cube.ppm", 800, 800);
	run_testfile("./tests/maps/box.rt", "box.ppm", 800, 800);
	run_testfile("./tests/maps/cylinder/cylinders.rt", "cylinders.ppm", 400, 600);
	run_testfile("./tests/maps/cylinder/cylinders_3light.rt", "cylinders_3light.ppm", 400, 600);
}
#endif
