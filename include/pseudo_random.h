/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_random.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:34:30 by afelger           #+#    #+#             */
/*   Updated: 2025/06/17 12:23:03 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PSEUDO_RANDOM_H
# define PSEUDO_RANDOM_H
# include "stdint.h"
# include "math.h"

uint32_t fast_rand();
double rand_double();
double linear_to_gamma(double linear_component);
#endif /* PSEUDO_RANDOM_H */
