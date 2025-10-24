#ifndef ELEMENTS_H
# define ELEMENTS_H
# include "ftvec3.h"

//The rgb: [0-255]
typedef struct s_rgb {
	int	r;
	int 	g;
	int 	b;
} t_rgb;

//Values [-inf, inf]
typedef t_vec3 t_point;

//Values [-1.0, 1.0]
typedef t_vec3 t_normal;

//The lighting ration: [0.0, 1.0]
typedef struct s_ambient_light {
	double	lighting_ratio;
	t_vec3	color;
} t_ambient_light;

//FOV: [0, 180]
typedef struct s_camera_o {
	t_point		loc;
	t_normal	normal;
	int			fov;
} t_camera_o;

//Brightness: [0.0, 1.0]
//RBG not used in mandatory part
typedef struct	s_light {
	t_point		loc;
	double		brightness;
	t_vec3		color;
} t_light;

typedef struct	s_sphere {
	t_point	loc;
	double	diameter;
	t_vec3	color;
} t_sphere;

typedef struct	s_plane {
	t_point		loc;
	t_normal	normal;
	t_vec3		color;
} t_plane;

typedef struct	s_cylinder{
	t_point		loc;
	t_normal	normal;
	double		diameter;
	double		height;
	t_vec3		color;
} t_cylinder;

#endif 
