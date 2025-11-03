#ifndef PARSER_H
# define PARSER_H
#include "elements.h"
#include "miniRT.h"
#include "object.h"

//parser.c
int	pars(const char *path, t_app *app);

//*.c
int	extract_ambient_light(const char *line, t_app *app);	
int	extract_camera(const char *line, t_app *app);
int	extract_light(const char *line, t_app *app);
int	extract_sphere(const char *line, t_app *app);
int	extract_plane(const char *line, t_app *app);
int	extract_cylinder(const char *line, t_app *app);
int	extract_triangle(const char *line, t_app *app);
int	extract_cone(const char *line, t_app *app);

//extract_rgb.c
void	cpy_rgb(t_vec3 *dst, t_vec3 *src);
t_vec3	extract_color(const char *input);

//extract_cordinates.c
void	cpy_loc(t_vec3 *dst, t_vec3 *src);
t_point	extract_loc(const char *input);

//extract_normal.c
void	cpy_normal(t_vec3 *dst, t_vec3 *src);
t_vec3	extract_normal(const char *input);

//token_utils.c
void	free_tokens(char **tokens);
int	token_ammount(char **tokens);
double	ft_atof(const char *input);
int	init_material(t_obj *obj);

//token_bonus.c
int pars_bonus_tokens(int last_mand_token, char **tokens, t_obj *sphere);

#endif
