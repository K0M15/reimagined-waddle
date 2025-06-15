/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:37:31 by afelger           #+#    #+#             */
/*   Updated: 2025/06/15 11:06:18 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int32_t ft_put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	uint8_t *pixel;

	pixel = &image->pixels[(y * image->width + x) * 4];
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
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

	app.width = 1600;
	app.height = 1500;
	ft_camera_init(
		&camera,
		FTVEC3(0),
		1.0,
		1.0 * (double)(app.width/app.height),
		1.0,
		app.width, app.height);
	app.active_camera = &camera;
	dyn_init(&app.hitable, sizeof(t_obj));
	t_obj sphere = ft_sphere_create(1,(t_vec3){0,0,-4});
	t_obj sphere1 = ft_sphere_create(1,(t_vec3){2,2,-10});
	t_obj sphere2 = ft_sphere_create(.5,(t_vec3){-1,-1,-2});
	dyn_add(&app.hitable, &sphere);
	dyn_add(&app.hitable, &sphere1);
	dyn_add(&app.hitable, &sphere2);
	if (setupWindow(&app) == EXIT_FAILURE)
		return (EXIT_FAILURE);	
	
	mlx_key_hook(app.mlx, key_hook, (void *) &app);
	mlx_loop_hook(app.mlx, draw_loop, (void *) &app);
	mlx_loop(app.mlx);
	mlx_terminate(app.mlx);
	return (EXIT_SUCCESS);
}