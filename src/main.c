/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:37:31 by afelger           #+#    #+#             */
/*   Updated: 2025/06/17 13:18:02 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int32_t ft_kumul_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	uint8_t *pixel;

	pixel = &image->pixels[(y * image->width + x) * 4];
	*(pixel) = ((uint8_t)(color >> 24) + *pixel) / 2;
	pixel++;
	*(pixel) = ((uint8_t)(color >> 16) + *pixel) / 2;
	pixel++;
	*(pixel) = ((uint8_t)(color >> 8) + *pixel) / 2;
	pixel++;
	*(pixel) = ((uint8_t)(color & 0xFF) + *pixel) / 2;
	return (0);
}	

int32_t ft_put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	uint8_t *pixel;

	pixel = &image->pixels[(y * image->width + x) * 4];
	*(pixel) = (uint8_t)(color >> 24);
	pixel++;
	*(pixel) = (uint8_t)(color >> 16);
	pixel++;
	*(pixel) = (uint8_t)(color >> 8);
	pixel++;
	*(pixel) = (uint8_t)(color & 0xFF);
	return (0);
}

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_app *app;

	app = (t_app *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(app->mlx);
}

void draw_loop(void *args)
{
	t_app *app;

	app = (t_app *)args;
	ft_camera_render(app, ft_put_pixel);
	// ft_camera_render(app, ft_kumul_pixel);
}

int32_t setupWindow(t_app *app)
{
	if (!(app->mlx = mlx_init(app->width, app->height, "MLX42", true)))
	{
		printf("%s\n", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(app->image = mlx_new_image(app->mlx, app->width, app->height)))
	{
		mlx_close_window(app->mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(app->mlx, app->image, 0, 0) == -1)
	{
		mlx_close_window(app->mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int32_t main(void)
{
	t_app app;
	t_camera camera;

	app.width = 1200;
	app.height = 800;
	ft_camera_init(
		&camera, (t_camera_p){FTVEC3(0), (t_vec3){0,0, -.8}, .5, 1.0 * (double)(app.width/app.height), 1.0, app.width, app.height, STAN_SAMPLES_PER_PIXEL});
	app.active_camera = &camera;

	dyn_init(&app.hitable, sizeof(t_obj));
	t_material material;
	memset(&material, 0, sizeof(t_material));
	material.color = (t_vec3) {155,255,255};
	material.reflectivity = 1.0;
	material.scatter = .1;
	t_obj sphere = ft_sphere_create((t_sphere_p){1,(t_vec3){0,0,-4}}, &material);
	t_obj sphere1 = ft_sphere_create((t_sphere_p){1,(t_vec3){2,2,-10}}, &material);
	t_obj sphere2 = ft_sphere_create((t_sphere_p){.5,(t_vec3){-1,-1,-2}}, &material);
	t_obj sphere3 = ft_sphere_create((t_sphere_p){50,(t_vec3){0,40,-100}}, &material);
	dyn_add(&app.hitable, &sphere);
	dyn_add(&app.hitable, &sphere1);
	dyn_add(&app.hitable, &sphere2);
	dyn_add(&app.hitable, &sphere3);
	if (setupWindow(&app) == EXIT_FAILURE)
		return (EXIT_FAILURE);	
	
	mlx_key_hook(app.mlx, key_hook, (void *) &app);
	mlx_loop_hook(app.mlx, draw_loop, (void *) &app);
	mlx_loop(app.mlx);
	mlx_terminate(app.mlx);
	return (EXIT_SUCCESS);
}