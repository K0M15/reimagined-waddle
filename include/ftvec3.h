/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftvec3.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:05:58 by afelger           #+#    #+#             */
/*   Updated: 2025/06/14 12:35:57 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VEC3_H
# define FT_VEC3_H

#include <stdint.h>
#include <math.h>

typedef struct s_vec3
{
    float x;
    float y;
    float z;
}	t_vec3;

# define FTVEC3(x) (t_vec3){x,x,x}

t_vec3 ftvec3_plus(t_vec3 op1, t_vec3 op2);
t_vec3 ftvec3_minus(t_vec3 op1, t_vec3 op2);
t_vec3 ftvec3_multiply(t_vec3 op1, t_vec3 op2);
t_vec3 ftvec3_divide(t_vec3 op1, t_vec3 op2);
float ftvec3_dot(t_vec3 op1, t_vec3 op2);
t_vec3 ftvec3_cross(t_vec3 op1, t_vec3 op2);
float ftvec3_length(t_vec3 vec);
t_vec3 ftvec3_normalize(t_vec3 vec);
t_vec3 ftvec3_unit(t_vec3 v);
uint32_t ftvec3_tocolor(t_vec3 v, float alpha);

#endif /* FT_VEC3_H */
