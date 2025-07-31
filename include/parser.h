#ifndef PARSER_H
# define PARSER_H
#include "settings.h"

//parser.c
int	pars(const char *path);

//*.c
int	extract_ambient_light(const char *line);	
int	extract_camera(const char *line);
int	extract_light(const char *line);
int	extract_sphere(const char *line);
int	extract_plane(const char *line);
int	extract_cylinder(const char *line);

//extract_utils.c
void	cpy_rgb(t_rgb *dst, t_rgb *src);
t_rgb	extract_color(const char *input);

//free_tokens.c
void	free_tokens(char **tokens);
int	token_ammount(char **tokens);
FLOAT	ft_atof(const char *input);

#endif
