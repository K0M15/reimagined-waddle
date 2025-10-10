

#include "hitable.h"
#include "libft.h"

t_material *createMaterial(int rgb[3], double reflectivity, double scatter, bool is_emitting)
{
	t_material *material = malloc(sizeof(t_material));
	if (material == NULL)
		return NULL;
	material->color = (t_vec3){(float) rgb[0], (float) rgb[1], (float) rgb[2]};
	material->reflectivity = reflectivity;
	material->scatter = scatter;
	material->is_emitting = is_emitting;
	return (material);
}

t_obj createPlane(char *str) // could be static
{
	//Type position normVecDirection color
	//  pl 0,0,0 0,1.0,0 255,0,225\n
	t_material *material = NULL;
	// int rgb[3];
	float posrot[6];
	// int i;
	(void) str;
	char ** data = ft_split(str, ' ');
	if (ft_strcmp(data[0], "pl"))
		return NULL; //error: false start token
	
	return (ft_plane_create((t_plane_p){
		(t_vec3){posrot[0], posrot[1], posrot[2]},
		(t_vec3){posrot[3], posrot[4], posrot[5]}}, material));
}

t_obj *createCylinder(char *str)
{
	//Type 
	// cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255\n
	(void) str;
	
	return NULL;
}

t_obj *createSphere(char *str)
{
	// sp 0,0,20 20 255,0,0\n
	(void) str;

	return NULL;
}

t_obj *createObject(char *str)
{
	(void) str;
	return NULL;

}

int parseFile(char *str, t_dyn *world)
{
	(void) str;
	(void) world;
	// open file and check
	// read file - gnl?
	// for each line there should be an object (if filled).
	// decide by first or second character, create element.
	return 0;
}