/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:22:08 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/03 20:22:13 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "object.h"
#include "parser.h"
#include <errno.h>
#include <stdio.h>

mlx_texture_t	*add_texture(char *src)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(src);
	if (!texture)
		printf("Texture: %s --- could not get loaded\n", src);
	return (texture);
}

int	extract_map_and_texture(int *iter, char **tokens,\
	t_obj *sphere, int last_mand_token)
{
	sphere->mat.tex = add_texture(tokens[*iter + last_mand_token]);
	if (!sphere->mat.tex)
		return (errno = EINVAL, -1);
	(*iter)++;
	sphere->mat.bump = add_texture(tokens[*iter + last_mand_token]);
	if (!sphere->mat.bump)
		return (errno = EINVAL, -1);
	return (0);
}

int	pars_bonus_tokens(int last_mand_token, char **tokens, t_obj *sphere)
{
	int	iter;

	iter = 1;
	sphere->mat.reflectivity = atof(tokens[iter + last_mand_token]);
	if (sphere->mat.reflectivity < 0 || sphere->mat.reflectivity > 1 || errno)
		return (errno = EINVAL, -1);
	iter++;
	sphere->mat.scatter = atof(tokens[iter + last_mand_token]);
	if (sphere->mat.scatter < 0 || sphere->mat.scatter > 1 || errno)
		return (errno = EINVAL, -1);
	iter++;
	sphere->mat.is_emitting = atof(tokens[iter + last_mand_token]);
	printf("%d\n", sphere->mat.is_emitting);
	if (errno)
		return (errno = EINVAL, -1);
	iter++;
	sphere->props.brightness = ft_atof(tokens[iter + last_mand_token]);
	if (sphere->props.brightness > (double)1.0
		|| sphere->props.brightness < (double)0.0 || errno)
		return (errno = EINVAL, -1);
	iter++;
	if (extract_map_and_texture(&iter, tokens, sphere, last_mand_token))
		return (errno = EINVAL, -1);
	return (0);
}
