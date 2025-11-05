/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:35:49 by afelger           #+#    #+#             */
/*   Updated: 2025/11/05 15:54:24 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_arr.h"
#include "libft.h"

int32_t	dyn_init(t_dyn *array)
{
	array->elem = malloc(DYN_INIT_S * sizeof(t_obj));
	if (array->elem == NULL)
		return (1);
	array->filled = 0;
	array->alloc = DYN_INIT_S;
	return (0);
}

int32_t	dyn_add(t_dyn *array, t_obj *element)
{
	if (array->filled + 1 >= array->alloc)
	{
		if (dyn_enhance(array))
			return (1);
	}
	ft_memcpy(array->elem + array->filled, element, sizeof(t_obj));
	array->filled++;
	return (0);
}

int32_t	dyn_enhance(t_dyn *array)
{
	t_obj	*replace;

	replace = malloc(array->alloc * 2 * sizeof(t_obj));
	if (replace == NULL)
		return (1);
	ft_memcpy(replace, array->elem, array->filled * sizeof(t_obj));
	free(array->elem);
	array->elem = replace;
	array->alloc = array->alloc * 2;
	return (0);
}

void	dyn_free(t_dyn *array)
{
	uint32_t	iter;

	iter = 0;
	if (array->elem)
	{
		while (iter < array->filled)
		{
			if ((array->elem + iter)->mat.tex)
			{
				mlx_delete_texture((array->elem + iter)->mat.tex);
			}
			if ((array->elem + iter)->mat.bump)
			{
				mlx_delete_texture((array->elem + iter)->mat.bump);
			}
			iter++;
		}
		free(array->elem);
	}
	return ;
}
