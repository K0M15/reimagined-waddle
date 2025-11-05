/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:22:08 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/05 15:14:29 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "object.h"
#include "parser.h"
#include <errno.h>
#include <stdio.h>
#include "libft.h"

#ifndef LOCALPATH
# define LOCALPATH ""
#endif /* LOCALPATH */

mlx_texture_t	*add_texture(char *src)
{
	char			*path;
	mlx_texture_t	*texture;

	texture = mlx_load_png(src);
	if (!texture)
	{
		printf("Texture: %s --- could not get loaded\n", src);
		path = ft_strjoin(LOCALPATH, src);
		texture = mlx_load_png(path);
		free(path);
	}
	return (texture);
}

int	extract_map_and_texture(int *iter, char **tokens,
	t_obj *sphere, int last_mand_token)
{
	sphere->mat.tex = add_texture(tokens[*iter + last_mand_token]);
	if (!sphere->mat.tex && *tokens[*iter + last_mand_token] != '*')
		return (errno = EINVAL, -1);
	(*iter)++;
	sphere->mat.bump = add_texture(tokens[*iter + last_mand_token]);
	if (!sphere->mat.bump && *tokens[*iter + last_mand_token] != '*')
		return (errno = EINVAL, -1);
	return (0);
}

int	pars_bonus_tokens(int last_mand_token, char **tokens, t_obj *sphere)
{
	int	iter;

	iter = 1;
	sphere->mat.reflectivity = ft_atof(tokens[iter + last_mand_token]);
	if (sphere->mat.reflectivity < 0 || sphere->mat.reflectivity > 1 || errno)
		return (errno = EINVAL, -1);
	iter++;
	sphere->mat.scatter = ft_atof(tokens[iter + last_mand_token]);
	if (sphere->mat.scatter < 0 || sphere->mat.scatter > 1 || errno)
		return (errno = EINVAL, -1);
	iter++;
	sphere->mat.is_emitting = ft_atof(tokens[iter + last_mand_token]);
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
