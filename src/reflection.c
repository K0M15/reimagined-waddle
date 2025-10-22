/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:48:59 by afelger           #+#    #+#             */
/*   Updated: 2025/10/17 16:52:47 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// source: https://p5js.org/reference/p5/lightFalloff
float	distance_col_scale(float distance)
{
	float	att;

	if (distance < 1e-6f)
		distance = 1e-6f;
	att = 1.0f / (1.0f + 0.1f * distance + 0.032f * distance * distance);
	att *= 6.0f;
	return (att);
}

void	ftref_lambert(struct s_ftray_color_props *p, t_point_light_p *pl,
	t_vec3 to_light)
{
	float	ndotl;

	ndotl = ftvec3_dot(p->rec.normal, ftvec3_unit(to_light));
	if (ndotl > 0.0f)
		p->light_acc = ftcol_add(p->light_acc, ftcol_mult(ftcol_scale(
						pl->color, pl->brightness * ndotl * distance_col_scale(
							ftvec3_length(to_light))), p->rec.mat->color));
}

void	ftref_phong(struct s_ftray_color_props *p, t_point_light_p *pl,
	t_vec3 to_light)
{
	t_vec3	reflect_dir;
	float	rdotv;

	reflect_dir = ftvec3_reflect(ftvec3_multiply(
				ftvec3_unit(to_light), ftvec3(-1)), p->rec.normal);
	rdotv = ftvec3_dot(ftvec3_unit(reflect_dir), p->view_dir);
	if (rdotv > 0.0f)
		p->light_acc = ftcol_add(p->light_acc,
				ftcol_scale(pl->color, pl->brightness * powf(
						rdotv, PHONG_SHININESS) * p->rec.mat->reflectivity
					* distance_col_scale(ftvec3_length(to_light))));
}
