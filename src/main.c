/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:37:31 by afelger           #+#    #+#             */
/*   Updated: 2025/10/25 16:24:11 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void ft_kumul_pixel(mlx_image_t *image, int x, int y, uint32_t color)
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
		((t_obj *)app->hitable.elem)->mat.reflectivity += .1;
	}

	if (keydata.key == MLX_KEY_G)
	{
		((t_obj *)app->hitable.elem)->mat.reflectivity -= .1;
	}
}

void draw_loop(void *args)
{
	t_app *app;

	app = (t_app *)args;
	ft_camera_render(app, ft_put_pixel);
	// ft_camera_render(app, ft_kumul_pixel);
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

#include <stdio.h>
#include "parser.h"

static void	print_instructions(void)
{
	printf("The program usage: ./miniRT [scene file]\n");
}

int32_t pars_init(int argc, char **argv, t_app *app)
{
	if (argc != 2)
	{
		print_instructions();
		return (-1);
	}
	dyn_init(&app->hitable, sizeof(t_obj));
	if (pars(argv[1], app) == -1)
		return (-1);
	return (0);
}

void	print_vec3(t_vec3 *vec)
{
	printf("%f,%f,%f", vec->x, vec->y, vec->z);
}

void	print_sphere(t_obj *app)
{
	print_vec3(&app->props.position);
	printf("\t");
	printf("%f", app->props.radius);
	printf("\t");
	print_vec3(&app->props.color);
}

void	print_cylinder(t_obj *app)
{
	print_vec3(&app->props.position);
	printf("\t");
	print_vec3(&app->props.rotation);
	printf("\t");
	printf("%f", app->props.radius);
	printf("\t");
	printf("%f", app->props.height);
	printf("\t");
	print_vec3(&app->props.color);
}

void	print_plane(t_obj *app)
{
	print_vec3(&app->props.position);
	printf("\t");
	print_vec3(&app->props.rotation);
	printf("\t");
	print_vec3(&app->props.color);
}

void	print_point_light(t_obj *app)
{
	print_vec3(&app->props.position);
	printf("\t");
	printf("%f", app->props.brightness);
	printf("\t");
	print_vec3(&app->props.color);
}

void	print_element(int iter, t_app *app)
{
	t_obj		*ptr;
	const char	*types[] = {"SPHERE", "CYLINDER", "PLANE", "POINT_LIGHT"};
	void	(*func[])(t_obj*)= {print_sphere, print_cylinder, print_plane, print_point_light};

	ptr = app->hitable.elem + iter;
	if (ptr->type == 0xFFFF)
	{
		printf("There is an error type in the objects!!/n");
		return ;
	}
	printf("==========\n");
	printf("The type: %s\n", types[ptr->type]);
	func[ptr->type](ptr);
	printf("\n");
	printf("The materials:\n color: %f, %f, %f; reflectivity: %f; is_emitting: %d; scatter: %f",\
			ptr->mat.color.x, ptr->mat.color.y, ptr->mat.color.z, ptr->mat.reflectivity,\
			ptr->mat.is_emitting, ptr->mat.scatter);
	printf("==========\n");
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

void add_material_to_objects(t_app *app)
{
	uint32_t	iter;
	t_obj		*ptr;

	iter = 0;
	while (iter < app->hitable.filled)
	{
		ptr = app->hitable.elem + iter;
		ptr->mat.color = ptr->props.color;
		ptr->mat.reflectivity = 0.1;
		ptr->mat.is_emitting = 0;
		ptr->mat.scatter = .5;
		if (ptr->type == POINT_LIGHT)
		{
			ptr->mat.is_emitting = 1;
			ptr->mat.reflectivity = 0.1;
		}
		iter++;
	}
}

void	resize_hook(int32_t width, int32_t height, void* param)
{
	t_app *app;

	app = (t_app *) param;

	app->width = width;
	app->height = height;
	app->active_camera->image_width = width;
	app->active_camera->image_height = height;
	ft_camera_calc(app->active_camera);
}

int32_t	main(int argc, char *argv[])
{
	t_app app;

	if (pars_init(argc, argv, &app) != 0)
		return (-1);
	t_camera camera;

	// Pars terminal and file inputs
	//TODO: convert to the different structures for the exec
	app.width = 1200;
	app.height = 800;
	ft_camera_init(
		&camera, (t_camera_p){
			ftvec3(0),
			(t_vec3){0,0, -1},
			90,
			app.width,
			app.height,
			STAN_SAMPLES_PER_PIXEL,
			// (t_vec3){0.5,0.9,1}
			// (t_vec3){66.0/255.0,245.0/255.0,135.0/255.0}
			(t_vec3){
				1, 1, 1
			},
			.2
		});
	app.active_camera = &camera;

	add_material_to_objects(&app);
	print_internal_data(&app);
	//t_obj sphere = ft_sphere_create((t_sphere_p){1,(t_vec3){2,2,-4}}, &material);
	//t_obj sphere1 = ft_sphere_create((t_sphere_p){1,(t_vec3){-3,5,-5}}, &material);
	// t_obj sphere1 = ft_sphere_create((t_sphere_p){1,(t_vec3){2,2,-10}}, &material);
	// t_obj sphere2 = ft_sphere_create((t_sphere_p){.5,(t_vec3){-1,-1,-2}}, &material);
	// t_obj sphere3 = ft_sphere_create((t_sphere_p){.1,(t_vec3){0,40,30}}, &mat_l);
	// t_obj sphere4 = ft_sphere_create((t_sphere_p){20,(t_vec3){0,10,30}}, &mat_l);
	//t_obj plane1 = ft_plane_create((t_plane_p){(t_vec3){0,-3,-10}, (t_vec3){0,1,0}}, &material2);
	// t_obj plane2 = ft_plane_create((t_plane_p){(t_vec3){0,-3,-10}, (t_vec3){0,0,1}}, &material2);
	// t_obj cyl1 = ft_cylinder_create((t_cylinder_p){10.0, 100.0, {0, 10, 10}, (t_vec3){1,0,0}}, &material);
	//t_obj lightsource = ft_light_create((t_point_light_p){(t_vec3){-3,8,-2}, .7f, (t_vec3){1, 1, 1}});
	// t_obj lightsource2 = ft_light_create((t_point_light_p){(t_vec3){1,0,-2}, 1.0f, (t_vec3){1, 1, 1}});
//	dyn_add(&app.hitable, &sphere);
//	dyn_add(&app.hitable, &sphere1);
	// dyn_add(&app.hitable, &sphere2);
	// dyn_add(&app.hitable, &sphere3);
//	dyn_add(&app.hitable, &plane1);
	//dyn_add(&app.hitable, &lightsource);
	// dyn_add(&app.hitable, &lightsource2);
	// dyn_add(&app.hitable, &plane2);
	// dyn_add(&app.hitable, &sphere4);
	// dyn_add(&app.hitable, &cyl1);
	// TODO: Still cleanup to do
	if (setupWindow(&app) == EXIT_FAILURE)
		return (EXIT_FAILURE);	
	
	mlx_key_hook(app.mlx, key_hook, (void *) &app);
	mlx_loop_hook(app.mlx, draw_loop, (void *) &app);
  	mlx_resize_hook(app.mlx, resize_hook, (void *) &app);
	mlx_loop(app.mlx);
	mlx_terminate(app.mlx);
	dyn_free(&app.hitable);
	return (EXIT_SUCCESS);
}

