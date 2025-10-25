#ifndef OBJECT_H
# define OBJECT_H

# include "ftvec3.h"
# include "MLX42.h"

enum e_obj_type{
    SPHERE,
    CYLINDER,
    PLANE,
    POINT_LIGHT,
    ERROR = 0xFFFF
};

typedef struct s_material
{
    double			reflectivity;
    double			scatter;
    t_vec3			color;
    bool			is_emitting;
    mlx_texture_t	*tex;
}   t_material;

/*TODO: Reorder the elements in order from largest to smallest*/
typedef struct	s_props{
	float   radius;
	float   diameter;
	float   height;
	t_vec3  position;
	t_vec3  rotation;
    float	brightness;
	t_vec3	color;
} t_props;

typedef struct s_obj
{
    enum e_obj_type type;
    t_props			props;
    t_material      mat;   //Maybe change object to have 
}   t_obj;

#endif
