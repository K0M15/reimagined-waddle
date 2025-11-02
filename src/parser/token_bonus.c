#include "miniRT.h"
#include "object.h"
#include "parser.h"
#include <errno.h>

mlx_texture_t*	add_texture(char *src)
{
	mlx_texture_t* texture;

	texture = mlx_load_png(src);
	return (texture);
}

int pars_bonus_tokens(int last_mand_token, char **tokens, t_obj *sphere)
{
	int		iter;

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
	if (sphere->props.brightness > (double)1.0 || sphere->props.brightness < (double)0.0 || errno)
		return (errno = EINVAL, -1);
	iter++;
	sphere->mat.tex = add_texture(tokens[iter + last_mand_token]);
	if (!sphere->mat.tex)
		return (errno = EINVAL, -1);
	iter++;
	sphere->mat.bump = add_texture(tokens[iter + last_mand_token]);
	if (!sphere->mat.bump)
		return (errno = EINVAL, -1);
	return (0);
}
