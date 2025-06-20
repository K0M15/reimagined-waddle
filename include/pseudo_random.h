/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_random.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:34:30 by afelger           #+#    #+#             */
/*   Updated: 2025/06/17 16:26:04 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PSEUDO_RANDOM_H
# define PSEUDO_RANDOM_H
# include "stdint.h"
# include "math.h"

uint32_t fast_rand();
double rand_double();
double linear_to_gamma(double linear_component);
double degrees_to_rad(double deg);
double rad_to_deg(double rad);

#endif /* PSEUDO_RANDOM_H */
