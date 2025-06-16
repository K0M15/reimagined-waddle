/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_random.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:33:51 by afelger           #+#    #+#             */
/*   Updated: 2025/06/16 16:34:21 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pseudo_random.h"

uint32_t fast_rand() {
    static uint32_t seed = 123456789; // Or initialize with a different value
    seed = 1664525 * seed + 1013904223;
    return seed;
}

double rand_double()
{
    double res = (double)((uint64_t)fast_rand() << 32 | fast_rand());
    return res / (double) UINT64_MAX;
}