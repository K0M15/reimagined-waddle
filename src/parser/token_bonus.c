#include "miniRT.h"
#include "objects.h"
#include "parser.h"

mlx_texture_t*	add_texture(char *src)
{
	mlx_texture_t* texture;

	texture = mlx_load_png(src);
	return (texture);
}

int pars_bonus_tokens(int last_mand_token, char **tokens, t_obj *sphere)
{
	const int	extra_tokens = 4;
	int		iter;

	iter = 1;
	sphere.mat.reflectivity = atof(tokens[iter + last_mand_token]);
	if (sphere.mat.reflectivity <= 0 || sphere.mat.reflectivity >= 1)
		return (errno = EIVAL, -1);
	iter++;
	sphere.mat.scatter = atof(tokens[iter + last_mand_token]);
	if (sphere.mat.scatter <= 0 || sphere.mat.scatter >= 1)
		return (errno = EIVAL, -1);
	iter++
	sphere.mat.tex = add_texture(tokens[iter + last_mand_token]);
	if (!sphere.mat.tex)
		return (errno = EIVAL, -1);
	sphere.mat.bump = add_texture(tokens[iter + last_mand_token]);
	if (!sphere.mat.tex)
		return (errno = EIVAL, -1);
	return (-1);
}
