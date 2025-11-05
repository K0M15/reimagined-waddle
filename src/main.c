/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:37:31 by afelger           #+#    #+#             */
/*   Updated: 2025/11/05 15:12:03 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include "parser.h"

int32_t	setupwindow(t_app *app)
{
	app->mlx = mlx_init(app->width, app->height, "MLX42", true);
	if (!app->mlx)
	{
		mlx_close_window(app->mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	app->image = mlx_new_image(app->mlx, app->width, app->height);
	if (!app->image)
	{
		mlx_close_window(app->mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(app->mlx, app->image, 0, 0) == -1)
	{
		mlx_close_window(app->mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int32_t	pars_init(int argc, char **argv, t_app *app)
{
	if (argc != 2)
	{
		print_instructions();
		return (-1);
	}
	if (dyn_init(&app->hitable))
		return (-1);
	if (pars(argv[1], app) == -1)
		return (dyn_free(&app->hitable), -1);
	ft_camera_calc(&app->active_camera);
	return (0);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_app	*app;

	app = (t_app *) param;
	app->width = width;
	app->height = height;
	app->active_camera.image_width = width;
	app->active_camera.image_height = height;
	mlx_delete_image(app->mlx, app->image);
	app->image = mlx_new_image(app->mlx, app->width, app->height);
	if (!app->image)
	{
		mlx_close_window(app->mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
	}
	if (mlx_image_to_window(app->mlx, app->image, 0, 0) == -1)
	{
		mlx_close_window(app->mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
	}
	ft_camera_calc(&app->active_camera);
}

#ifdef PROD

void	draw_loop(void *args)
{
	t_app			*app;
	static uint32_t	lastpixel;

	app = (t_app *)args;
	lastpixel = ft_camera_render(app, ft_put_pixel, lastpixel,
			lastpixel + 1000 / STAN_SAMPLES_PER_PIXEL);
}

int32_t	main(int argc, char *argv[])
{
	t_app	app;

	init_default_camera(&app);
	if (pars_init(argc, argv, &app) != 0)
		return (-1);
	print_internal_data(&app);
	if (setupwindow(&app) == EXIT_FAILURE)
		return (dyn_free(&app.hitable), EXIT_FAILURE);
	mlx_key_hook(app.mlx, key_hook, (void *) &app);
	mlx_loop_hook(app.mlx, draw_loop, (void *) &app);
	mlx_resize_hook(app.mlx, resize_hook, (void *) &app);
	mlx_loop(app.mlx);
	mlx_delete_image(app.mlx, app.image);
	mlx_terminate(app.mlx);
	dyn_free(&app.hitable);
	return (EXIT_SUCCESS);
}
#endif
