/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:35:49 by afelger           #+#    #+#             */
/*   Updated: 2025/06/14 16:31:42 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_arr.h"

int	dyn_init(t_dyn *array, uint8_t mem_size)
{
	array->elem = malloc(DYN_INIT_S * mem_size);
	if (array->elem == NULL)
        return (1);
	array->filled = 0;
	array->alloc = DYN_INIT_S;
    array->mem_size = mem_size;
	return (0);
}

int	dyn_add(t_dyn *array, void *element)
{
	if (array->filled + 1 >= array->alloc)
	{
		if (dyn_enhance(array))
			return (1);
	}
    memcpy(&(array->elem[array->filled * array->mem_size]), element, array->mem_size);
	array->filled++;
	return (0);
}

int	dyn_enhance(t_dyn *array)
{
	void			**replace;
	unsigned int	i;

	replace = malloc(array->alloc * 2 * array->mem_size);
	if (replace == NULL)
		return (1);
	i = 0;
    memcpy(replace, array->elem, array->filled*array->mem_size);
    free(array->elem);
	array->elem = replace;
	array->alloc = array->alloc * 2;
	return (0);
}

void dyn_dest(t_dyn *arr)
{
    free(arr->elem);
}