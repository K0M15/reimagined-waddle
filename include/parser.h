#ifndef PARSER_H
# define PARSER_H
#include "settings.h"
#include "elements.h"
#include "miniRT.h"

//parser.c
int	pars(const char *path, t_app *app);

//*.c
int	extract_ambient_light(const char *line, t_app *app);	
int	extract_camera(const char *line, t_app *app);
int	extract_light(const char *line, t_app *app);
int	extract_sphere(const char *line, t_app *app);
int	extract_plane(const char *line, t_app *app);
int	extract_cylinder(const char *line, t_app *app);

//extract_rgb.c
void	cpy_rgb(t_vec3 *dst, t_vec3 *src);
t_vec3	extract_color(const char *input);

//extract_cordinates.c
void	cpy_loc(t_vec3 *dst, t_vec3 *src);
t_point	extract_loc(const char *input);

//extract_normal.c
void	cpy_normal(t_vec3 *dst, t_vec3 *src);
t_vec3	extract_normal(const char *input);

//free_tokens.c
void	free_tokens(char **tokens);
int	token_ammount(char **tokens);
FLOAT	ft_atof(const char *input);

#endif
