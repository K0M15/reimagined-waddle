/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:04:02 by afelger           #+#    #+#             */
/*   Updated: 2025/10/17 16:40:01 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "ftcolor.h"
#include "ftvec3.h"

// t_obj	ft_light_create(t_point_light_p props)
// {
// 	t_obj	light;

// 	light.type = ERROR;
// 	light.props = malloc(sizeof(t_point_light_p));
// 	if (!light.props)
// 		return (light);
// 	light.type = POINT_LIGHT;
// 	light.mat = NULL;
// 	memcpy(light.props, &props, sizeof(t_point_light_p));
// 	return (light);
// }
