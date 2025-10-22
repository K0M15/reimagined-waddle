/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftvec3_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:09:27 by afelger           #+#    #+#             */
/*   Updated: 2025/10/16 13:09:41 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvec3.h"

t_vec3	ftvec3_minus(t_vec3 op1, t_vec3 op2)
{
	t_vec3	result;

	result.x = op1.x - op2.x;
	result.y = op1.y - op2.y;
	result.z = op1.z - op2.z;
	return (result);
}

t_vec3	ftvec3_multiply(t_vec3 op1, t_vec3 op2)
{
	t_vec3	result;

	result.x = op1.x * op2.x;
	result.y = op1.y * op2.y;
	result.z = op1.z * op2.z;
	return (result);
}

t_vec3	ftvec3_divide(t_vec3 op1, t_vec3 op2)
{
	t_vec3	result;

	if (op2.x != 0)
		result.x = op1.x / op2.x;
	else
		result.x = 0;
	if (op2.y != 0)
		result.y = op1.y / op2.y;
	else
		result.y = 0;
	if (op2.z != 0)
		result.z = op1.z / op2.z;
	else
		result.z = 0;
	return (result);
}

float	ftvec3_dot(t_vec3 op1, t_vec3 op2)
{
	return (op1.x * op2.x + op1.y * op2.y + op1.z * op2.z);
}

t_vec3	ftvec3_cross(t_vec3 op1, t_vec3 op2)
{
	t_vec3	result;

	result.x = op1.y * op2.z - op1.z * op2.y;
	result.y = op1.z * op2.x - op1.x * op2.z;
	result.z = op1.x * op2.y - op1.y * op2.x;
	return (result);
}
