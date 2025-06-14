/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftvec3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:51:41 by afelger           #+#    #+#             */
/*   Updated: 2025/06/14 13:39:25 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvec3.h"

t_vec3 ftvec3_plus(t_vec3 op1, t_vec3 op2)
{
    t_vec3 result;

    result.x = op1.x + op2.x;
    result.y = op1.y + op2.y;
    result.z = op1.z + op2.z;

    return result;
}

t_vec3 ftvec3_minus(t_vec3 op1, t_vec3 op2)
{
    t_vec3 result;

    result.x = op1.x - op2.x;
    result.y = op1.y - op2.y;
    result.z = op1.z - op2.z;

    return result;
}
t_vec3 ftvec3_multiply(t_vec3 op1, t_vec3 op2)
{
    t_vec3 result;

    result.x = op1.x * op2.x;
    result.y = op1.y * op2.y;
    result.z = op1.z * op2.z;

    return result;
}
t_vec3 ftvec3_divide(t_vec3 op1, t_vec3 op2)
{
    t_vec3 result;

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

    return result;
}
float ftvec3_dot(t_vec3 op1, t_vec3 op2)
{
    return (op1.x * op2.x + op1.y * op2.y + op1.z * op2.z);
}
t_vec3 ftvec3_cross(t_vec3 op1, t_vec3 op2)
{
    t_vec3 result;

    result.x = op1.y * op2.z - op1.z * op2.y;
    result.y = op1.z * op2.x - op1.x * op2.z;
    result.z = op1.x * op2.y - op1.y * op2.x;

    return result;
}
float ftvec3_length(t_vec3 vec)
{
    return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
t_vec3 ftvec3_normalize(t_vec3 vec)
{
    float length;
    t_vec3 result;

    length = ftvec3_length(vec);
    if (length != 0)
    {
        result.x = vec.x / length;
        result.y = vec.y / length;
        result.z = vec.z / length;
    }
    else
    {
        result.x = 0;
        result.y = 0;
        result.z = 0;
    }
    return result;
}

t_vec3 ftvec3_unit(t_vec3 v)
{
    float length;

    length = ftvec3_length(v);
    return ftvec3_divide(v, (t_vec3) {length, length, length});
}

uint32_t ftvec3_tocolor(t_vec3 v, float alpha)
{
    uint32_t r = (uint32_t)(fminf(fmaxf(v.x, 0.0f), 1.0f) * 255.0f);
    uint32_t g = (uint32_t)(fminf(fmaxf(v.y, 0.0f), 1.0f) * 255.0f);
    uint32_t b = (uint32_t)(fminf(fmaxf(v.z, 0.0f), 1.0f) * 255.0f);
    uint32_t a = (uint32_t)(fminf(fmaxf(alpha, 0.0f), 1.0f) * 255.0f);

    return (r << 24) | (g << 16) | (b << 8) | a;
}