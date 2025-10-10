<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:37:31 by afelger           #+#    #+#             */
/*   Updated: 2025/10/10 10:10:04 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void ft_kumul_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	uint8_t *pixel;

	pixel = &image->pixels[(y * image->width + x) * 4];
	*(pixel) = ((uint8_t)(color >> 24) + *pixel);
	pixel++;
	*(pixel) = ((uint8_t)(color >> 16) + *pixel);
	pixel++;
	*(pixel) = ((uint8_t)(color >> 8) + *pixel);
	pixel++;
	*(pixel) = ((uint8_t)(color & 0xFF) + *pixel);
}	

void ft_put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
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
}

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_app *app;

	app = (t_app *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(app->mlx);
	if (keydata.key == MLX_KEY_W)
		ft_camera_apply(app->active_camera, (t_vec3){0, MOV_SPEED, 0});
	if (keydata.key == MLX_KEY_S)
		ft_camera_apply(app->active_camera, (t_vec3){0, -MOV_SPEED, 0});
	if (keydata.key == MLX_KEY_A)
		ft_camera_apply(app->active_camera, (t_vec3){MOV_SPEED, 0, 0});
	if (keydata.key == MLX_KEY_D)
		ft_camera_apply(app->active_camera, (t_vec3){-MOV_SPEED, 0, 0});
	if (keydata.key == MLX_KEY_Q)
	{
		app->active_camera->fov *= 1.1;
		ft_camera_calc(app->active_camera);
	}
	if (keydata.key == MLX_KEY_E)
	{
		app->active_camera->fov *= 0.90909090909090909090;
		ft_camera_calc(app->active_camera);
	}
	if (keydata.key == MLX_KEY_T)
	{
		((t_obj *)app->hitable.elem)->mat->reflectivity += .1;
	}

	if (keydata.key == MLX_KEY_G)
	{
		((t_obj *)app->hitable.elem)->mat->reflectivity -= .1;
	}
}

void draw_loop(void *args)
{
	t_app *app;

	app = (t_app *)args;
	// ft_camera_render(app, ft_put_pixel);
	ft_camera_render(app, ft_kumul_pixel);
	printf("Cam: X%.2f Y%.2f Z%.2f, FOV%.2F\n", app->active_camera->look_at.x, app->active_camera->look_at.y, app->active_camera->look_at.z, app->active_camera->fov);
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
		&camera, (t_camera_p){
			FTVEC3(0),
			(t_vec3){0,0, -1},
			90,
			app.width,
			app.height,
			STAN_SAMPLES_PER_PIXEL,
			// (t_vec3){0.5,0.9,1}
			// (t_vec3){66.0/255.0,245.0/255.0,135.0/255.0}
			(t_vec3){1.0*255.0/255.0,1.0*255.0/255.0,1.0*255.0/255.0}
		});
	app.active_camera = &camera;

	dyn_init(&app.hitable, sizeof(t_obj));

	t_material material;
	memset(&material, 0, sizeof(t_material));
	material.color = (t_vec3) {1, 1, 0};
	material.reflectivity = .1;
	material.is_emitting = 0;
	material.scatter = .7;

	t_material mat_l;
	memset(&mat_l, 0, sizeof(t_material));
	mat_l.color = (t_vec3) {1,1,1};
	mat_l.reflectivity = 0.0;
	mat_l.is_emitting = 1;
	mat_l.scatter = .5;
	
	t_obj sphere = ft_sphere_create((t_sphere_p){1,(t_vec3){0,0,-4}}, &material);
	t_obj sphere1 = ft_sphere_create((t_sphere_p){1,(t_vec3){2,2,-10}}, &material);
	t_obj sphere2 = ft_sphere_create((t_sphere_p){.5,(t_vec3){-1,-1,-2}}, &material);
	t_obj sphere3 = ft_sphere_create((t_sphere_p){.1,(t_vec3){0,40,30}}, &mat_l);
	// t_obj sphere4 = ft_sphere_create((t_sphere_p){20,(t_vec3){0,10,30}}, &mat_l);
	dyn_add(&app.hitable, &sphere);
	dyn_add(&app.hitable, &sphere1);
	dyn_add(&app.hitable, &sphere2);
	dyn_add(&app.hitable, &sphere3);
	// dyn_add(&app.hitable, &sphere4);
	if (setupWindow(&app) == EXIT_FAILURE)
		return (EXIT_FAILURE);	
	
	mlx_key_hook(app.mlx, key_hook, (void *) &app);
	mlx_loop_hook(app.mlx, draw_loop, (void *) &app);
	mlx_loop(app.mlx);
	mlx_terminate(app.mlx);
	return (EXIT_SUCCESS);
}
/*
#include <stdio.h>
#include "parser.h"
#include "minirt.h"

static void	print_instructions(void)
{
	printf("The program usage: ./miniRT [scene file]\n");
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		print_instructions();
		return (-1);
	}
	if (pars(argv[1]) == -1)
		return (-1);
	//TODO: Implement after parsing function
	return (0);
>>>>>>> rt_temp/temp
}
*/
