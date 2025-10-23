/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_arr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:04:10 by afelger           #+#    #+#             */
/*   Updated: 2025/10/23 15:59:33 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYN_ARR_H
# define DYN_ARR_H
# include "stdlib.h"
# include "stddef.h"
# include "stdint.h"
# include "string.h"
# include "object.h"
# define DYN_INIT_S 300

typedef struct s_dyn
{
	t_obj	    *elem;
	uint32_t	filled;
	uint32_t	alloc;
}	t_dyn;

int32_t dyn_add(t_dyn *array, t_obj *element);
int32_t dyn_init(t_dyn *array);
int32_t	dyn_enhance(t_dyn *array);
void	dyn_free(t_dyn *array);

#endif /* DYN_ARR_H */
