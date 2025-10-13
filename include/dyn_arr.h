/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_arr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:04:10 by afelger           #+#    #+#             */
/*   Updated: 2025/10/11 11:08:04 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYN_ARR_H
# define DYN_ARR_H
# include "stdlib.h"
# include "stddef.h"
# include "stdint.h"
# include "string.h"
# define DYN_INIT_S 300

typedef struct s_dyn
{
	void		*elem;
	uint32_t	filled;
	uint32_t	alloc;
	uint8_t		mem_size;
}	t_dyn;

int32_t	dyn_add(t_dyn *array, void *element);
void	dyn_dest(t_dyn *arr);
int32_t	dyn_init(t_dyn *array, uint8_t mem_size);
int32_t	dyn_enhance(t_dyn *array);

#endif /* DYN_ARR_H */