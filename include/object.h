/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:34:15 by afelger           #+#    #+#             */
/*   Updated: 2025/10/28 14:40:28 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "ftvec3.h"
# include "MLX42.h"

enum e_obj_type
{
	SPHERE,
	CYLINDER,
	PLANE,
	POINT_LIGHT,
	ERROR = 0xFFFF
};

typedef struct s_material
{
	t_vec3			color;
	double			reflectivity;
	double			scatter;
	bool			is_emitting;
	mlx_texture_t	*tex;
	mlx_texture_t	*bump;
}	t_material;

typedef struct s_props
{
	t_vec3	color;
	t_vec3	position;
	t_vec3	rotation;
	float	radius;
	float	diameter;
	float	height;
	float	brightness;
}	t_props;

typedef struct s_obj
{
	t_props			props;
	t_material		mat;
	enum e_obj_type	type;
}	t_obj;

#endif
