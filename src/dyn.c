/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:35:49 by afelger           #+#    #+#             */
/*   Updated: 2025/10/22 13:10:44 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_arr.h"

int32_t dyn_init(t_dyn *array, uint8_t mem_size)
{
	array->elem = malloc(DYN_INIT_S * mem_size);
	if (array->elem == NULL)
        return (1);
	array->filled = 0;
	array->alloc = DYN_INIT_S;
    array->mem_size = mem_size;
	return (0);
}

#include "stdio.h"
int32_t dyn_add(t_dyn *array, t_obj *element)
{
	printf("New element added radius: %f\n", element->props.radius);
	if (array->filled + 1 >= array->alloc)
	{
		if (dyn_enhance(array))
			return (1);
	}
    memcpy(array->elem + array->filled, element, array->mem_size);
	array->filled++;
	return (0);
}

int32_t dyn_enhance(t_dyn *array)
{
	t_obj			*replace;

	replace = malloc(array->alloc * 2 * array->mem_size);
	if (replace == NULL)
		return (1);
    memcpy(replace, array->elem, array->filled*array->mem_size);
    free(array->elem);
	array->elem = replace;
	array->alloc = array->alloc * 2;
	return (0);
}

void	dyn_free(t_dyn *array)
{
	if (array->elem)
		free(array->elem);
	return ;
}
