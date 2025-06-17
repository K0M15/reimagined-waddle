/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftvec3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:51:41 by afelger           #+#    #+#             */
/*   Updated: 2025/06/17 13:14:58 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvec3.h"

t_vec3 ftvec3_reflect(t_vec3 vec, t_vec3 norm)
{
    t_vec3 dot;

    dot = FTVEC3(ftvec3_dot(vec, norm));
    return ftvec3_minus(vec, ftvec3_multiply(FTVEC3(2), ftvec3_multiply(dot, norm)));
}

bool ftvec3_near_zero(t_vec3 vec)
{
    return ((fabs(vec.x) < DOUBLE_NEAR_ZERO) &&
        (fabs(vec.y) < DOUBLE_NEAR_ZERO) &&
        (fabs(vec.z) < DOUBLE_NEAR_ZERO));
}

t_vec3 ftvec3_lin_gamma(t_vec3 vec)
{
    return (t_vec3) {
        linear_to_gamma(vec.x),
        linear_to_gamma(vec.y),
        linear_to_gamma(vec.z)
    };
}

double clamp(double f, double min, double max)
{
    if (f < min)
        return (min);
    if (f > max)
        return (max);
    return f;
}

t_vec3 ftvec3_random()
{
    return (t_vec3){ rand_double(), rand_double(), rand_double() };
}

t_vec3 ftvec3_rclamped(double min, double max)
{
    double scale;

    scale = max - min;
    return (t_vec3){
        clamp((rand_double() - 0.5) * scale, min, max),
        clamp((rand_double() - 0.5) * scale, min, max),
        clamp((rand_double() - 0.5) * scale, min, max)
    };
}

t_vec3 ftvec3_runit()
{
    t_vec3 p;
    double lensq;
    
    p = ftvec3_rclamped(-1, 1);
    lensq = ftvec3_length(p) * ftvec3_length(p);
    while (1e160 < lensq && lensq <= 1)
    {
        p = ftvec3_rclamped(-1, 1);
        lensq = ftvec3_length(p) * ftvec3_length(p);
    }
    return ftvec3_divide(p, FTVEC3(sqrt(lensq)));
}

t_vec3 ftvec3_ronhemi(t_vec3 normal)
{
    t_vec3 on_hemi;

    on_hemi = ftvec3_runit();
    if (ftvec3_dot(on_hemi, normal) > 0.0)
        return on_hemi;
    return ftvec3_multiply(on_hemi, FTVEC3(-1));
}

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
    uint32_t r = (uint32_t)(clamp(v.x, 0, 1) * 255.0f);
    uint32_t g = (uint32_t)(clamp(v.y, 0, 1) * 255.0f);
    uint32_t b = (uint32_t)(clamp(v.z, 0, 1) * 255.0f);
    uint32_t a = (uint32_t)(clamp(alpha, 0, 1) * 255.0f);

    return (r << 24) | (g << 16) | (b << 8) | a;
}