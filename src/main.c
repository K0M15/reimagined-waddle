/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:37:31 by afelger           #+#    #+#             */
/*   Updated: 2025/11/04 20:55:47 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include "parser.h"

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_app *app;

	app = (t_app *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(app->mlx);
	if (keydata.key == MLX_KEY_W)
		ft_camera_apply(&app->active_camera, (t_vec3){0, MOV_SPEED, 0});
	if (keydata.key == MLX_KEY_S)
		ft_camera_apply(&app->active_camera, (t_vec3){0, -MOV_SPEED, 0});
	if (keydata.key == MLX_KEY_A)
		ft_camera_apply(&app->active_camera, (t_vec3){MOV_SPEED, 0, 0});
	if (keydata.key == MLX_KEY_D)
		ft_camera_apply(&app->active_camera, (t_vec3){-MOV_SPEED, 0, 0});
	if (keydata.key == MLX_KEY_DOWN)
		ft_camera_move(&app->active_camera, (t_vec3){0, 0, -MOV_SPEED});
	if (keydata.key == MLX_KEY_UP)
		ft_camera_move(&app->active_camera, (t_vec3){0, 0, MOV_SPEED});
	if (keydata.key == MLX_KEY_LEFT)
		ft_camera_move(&app->active_camera, (t_vec3){-MOV_SPEED, 0, 0});
	if (keydata.key == MLX_KEY_RIGHT)
		ft_camera_move(&app->active_camera, (t_vec3){MOV_SPEED, 0, 0});
	if (keydata.key == MLX_KEY_Q)
	{
		app->active_camera.fov *= 1.1;
		ft_camera_calc(&app->active_camera);
	}
	if (keydata.key == MLX_KEY_E)
	{
		app->active_camera.fov *= 0.90909090909090909090;
		ft_camera_calc(&app->active_camera);
	}
	if (keydata.key == MLX_KEY_T)
	{
		((t_obj *)app->hitable.elem)->mat.reflectivity += .1;
	}
	if (keydata.key == MLX_KEY_G)
	{
		((t_obj *)app->hitable.elem)->mat.reflectivity -= .1;
	}
	if (keydata.key == MLX_KEY_0)
		checker_enable(3);
	if (keydata.key == MLX_KEY_1)
		checker_enable(1);
}

int32_t setupWindow(t_app *app)
{
	if (!(app->mlx = mlx_init(app->width, app->height, "MLX42", true)))
	{
		mlx_close_window(app->mlx);
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

int32_t pars_init(int argc, char **argv, t_app *app)
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

void print_internal_data(t_app *app)
{
	uint32_t	iter;

	iter = 0;
	while (iter < app->hitable.filled)
	{
		print_element(iter, app);
		iter++;
	}
	return ;
}

void	resize_hook(int32_t width, int32_t height, void* param)
{
	t_app *app;

	app = (t_app *) param;
	app->width = width;
	app->height = height;
	app->active_camera.image_width = width;
	app->active_camera.image_height = height;
	printf("The height: %d, the width: %d\n", app->mlx->height, app->mlx->width);
	mlx_delete_image(app->mlx, app->image);
	if (!(app->image = mlx_new_image(app->mlx, app->width, app->height)))
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
void draw_loop(void *args)
{
	t_app			*app;
	static uint32_t	lastPixl;

	app = (t_app *)args;
	lastPixl = ft_camera_render(app, ft_put_pixel, lastPixl, lastPixl + 1000 / STAN_SAMPLES_PER_PIXEL);
}

int32_t	main(int argc, char *argv[])
{
	t_app app;
	init_default_camera(&app);
	if (pars_init(argc, argv, &app) != 0)
		return (-1);
	print_internal_data(&app);
	if (setupWindow(&app) == EXIT_FAILURE)
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
