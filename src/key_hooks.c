/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:40:28 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/05 13:40:30 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#ifndef MOVE

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = (t_app *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(app->mlx);
	if (keydata.key == MLX_KEY_0)
		checker_enable(3);
	if (keydata.key == MLX_KEY_1)
		checker_enable(1);
}
#endif
#ifdef MOVE

void	apply_movement_keys(mlx_key_data_t *keydata, t_app *app)
{
	if (keydata->key == MLX_KEY_W)
		ft_camera_apply(&app->active_camera, (t_vec3){0, MOV_SPEED, 0});
	if (keydata->key == MLX_KEY_S)
		ft_camera_apply(&app->active_camera, (t_vec3){0, -MOV_SPEED, 0});
	if (keydata->key == MLX_KEY_A)
		ft_camera_apply(&app->active_camera, (t_vec3){MOV_SPEED, 0, 0});
	if (keydata->key == MLX_KEY_D)
		ft_camera_apply(&app->active_camera, (t_vec3){-MOV_SPEED, 0, 0});
	if (keydata->key == MLX_KEY_DOWN)
		ft_camera_move(&app->active_camera, (t_vec3){0, 0, -MOV_SPEED});
	if (keydata->key == MLX_KEY_UP)
		ft_camera_move(&app->active_camera, (t_vec3){0, 0, MOV_SPEED});
	if (keydata->key == MLX_KEY_LEFT)
		ft_camera_move(&app->active_camera, (t_vec3){-MOV_SPEED, 0, 0});
	if (keydata->key == MLX_KEY_RIGHT)
		ft_camera_move(&app->active_camera, (t_vec3){MOV_SPEED, 0, 0});
}

void	apply_scaling_keys(mlx_key_data_t *keydata, t_app *app)
{
	if (keydata->key == MLX_KEY_Q)
	{
		app->active_camera.fov *= 1.1;
		ft_camera_calc(&app->active_camera);
	}
	if (keydata->key == MLX_KEY_E)
	{
		app->active_camera.fov *= 0.90909090909090909090;
		ft_camera_calc(&app->active_camera);
	}
	if (keydata->key == MLX_KEY_T)
	{
		((t_obj *)app->hitable.elem)->mat.reflectivity += .1;
	}
	if (keydata->key == MLX_KEY_G)
	{
		((t_obj *)app->hitable.elem)->mat.reflectivity -= .1;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = (t_app *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(app->mlx);
	apply_movement_keys(&keydata, app);
	apply_scaling_keys(&keydata, app);
	if (keydata.key == MLX_KEY_0)
		checker_enable(3);
	if (keydata.key == MLX_KEY_1)
		checker_enable(1);
}
#endif
