/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftcamera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:54:06 by afelger           #+#    #+#             */
/*   Updated: 2025/09/05 14:53:18 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void ft_camera_calc(t_camera *camera)
{
    double h;
    
    h = tan(degrees_to_rad(camera->fov) / 2);
    camera->focal_length = ftvec3_length(ftvec3_minus(camera->center, camera->look_at));
    camera->viewport_height = 2 * h * camera->focal_length;
    camera->viewport_width = camera->viewport_height * ((double)camera->image_width / (double)camera->image_height);
    camera->w = ftvec3_unit(ftvec3_minus(camera->center, camera->look_at));
    camera->u = ftvec3_unit(ftvec3_cross(camera->w, camera->vec_up));
    camera->v = ftvec3_cross(camera->w, camera->u);
    camera->viewport_u = ftvec3_multiply(camera->u, FTVEC3(camera->viewport_width));
    camera->viewport_v = ftvec3_multiply(camera->v, FTVEC3(camera->viewport_height));
    camera->delta_u = ftvec3_divide(camera->viewport_u, FTVEC3(camera->image_width));
    camera->delta_v = ftvec3_divide(camera->viewport_v, FTVEC3(camera->image_height));
    camera->vupper_left = ftvec3_minus(camera->center, ftvec3_multiply(FTVEC3(camera->focal_length), camera->w));
    camera->vupper_left = ftvec3_minus(camera->vupper_left, ftvec3_divide(camera->viewport_u, FTVEC3(2)));
    camera->vupper_left = ftvec3_minus(camera->vupper_left, ftvec3_divide(camera->viewport_v, FTVEC3(2)));
}

uint32_t ft_camera_init(t_camera *camera, t_camera_p props)
{
    camera->vec_up = (t_vec3) {0, 1, 0};
    camera->center = props.center;
    camera->look_at = props.look_at;
    camera->fov = props.fov;
    camera->image_width = props.imageWidth;
    camera->image_height = props.imageHeight;
    ft_camera_calc(camera);
    camera->samples_per_pixel = props.samples_per_pixel;
    camera->ambient = props.ambient;
    return (0);
}

t_obj ft_sphere_create(t_sphere_p params, t_material *mat)
{
    t_obj sphere;

    sphere.type = ERROR;
    if(!(sphere.props = malloc(sizeof(t_sphere_p))))
        return sphere;
    sphere.type = SPHERE;
    sphere.mat = mat;
    memcpy(sphere.props, &params, sizeof(t_sphere_p));
    return sphere;
}

void ft_hitr_set_face_normal(t_hitrec *rec, t_ray ray, t_vec3 outwar_norm)
{
    rec->front_face = ftvec3_dot(ray.direction, outwar_norm) < 0;
    if (rec->front_face)
        rec->normal = outwar_norm;
    else
        rec->normal = ftvec3_multiply(outwar_norm, FTVEC3(-1));
}

uint32_t ft_sphere_hit(t_obj sphere, t_ray ray, double min, double max, t_hitrec *rec)
{
    t_vec3 oc;
    t_vec3 abc;
    float disciminant;
    float root;

    oc = ftvec3_minus(((t_sphere_p *)sphere.props)->position, ray.origin);
    abc = (t_vec3) {
        ftvec3_dot(ray.direction, ray.direction),
        ftvec3_dot(ray.direction, oc),
        ftvec3_dot(oc, oc) - ((t_sphere_p *)sphere.props)->radius * ((t_sphere_p *)sphere.props)->radius
    };
    disciminant = (abc.y*abc.y - abc.x * abc.z);
    if (disciminant < 0)
        return 0;
    disciminant = sqrtf(disciminant);
    root = (abc.y - disciminant) / abc.x;
    if (root <= min || max <= root)
    {
        root = (abc.y + disciminant) / abc.x;
        if (root <= min || max <= root)
            return false;
    }
    rec->t = root;
    rec->hit = ftray_at(ray, root);
    ft_hitr_set_face_normal(rec, ray, ftvec3_divide(ftvec3_minus(rec->hit,((t_sphere_p *)sphere.props)->position), FTVEC3(((t_sphere_p *)sphere.props)->radius)));
    return true;
}

void ft_obj_dest(t_obj sphere)
{
    free(sphere.props);
}

t_obj   ft_cylinder_create(t_cylinder_p params, t_material *mat)
{
    t_obj cyl;

    cyl.type = ERROR;
    if(!(cyl.props = malloc(sizeof(t_cylinder_p))))
        return cyl;
    cyl.type = CYLINDER;
    cyl.mat = mat;
    memcpy(cyl.props, &params, sizeof(t_cylinder_p));
    return (cyl);
}

t_obj   ft_plane_create(t_plane_p params, t_material *mat)
{
    t_obj plane;

    plane.type = ERROR;
    if(!(plane.props = malloc(sizeof(t_plane_p))))
        return plane;
    plane.type = PLANE;
    plane.mat = mat;
    memcpy(plane.props, &params, sizeof(t_plane_p));
    return (plane);
}

t_ray ft_mat_scatter(t_ray inc, t_hitrec *rec)
{
    (void) inc;
    t_ray out;
    out.origin = rec->hit;
    //TODO:  insert inteligent scatter logic OR delete it since only specular reflections are needed
    if (rand_double() < rec->mat->scatter)
        out.direction = ftvec3_plus(ftvec3_ronhemi(rec->normal), rec->normal);
    else
        out.direction = ftvec3_reflect(inc.direction, rec->normal);
    return out;
}

// TODO: work on nudge -> https://stackoverflow.com/questions/41211892/ray-tracer-artifacts-with-reflection
uint32_t world_hit(t_dyn *world, t_ray ray, double min, double max, t_hitrec *rec)
{
    t_hitrec temp;
    uint32_t anything = 0;
    double closest = max;
    uint32_t ctr = 0;
    while (ctr < world->filled)
    {
        t_obj *obj = world->elem + ctr*world->mem_size;
        uint32_t hit = 0;
        if (obj->type == SPHERE)
            hit = ft_sphere_hit(*obj, ray, min, max, &temp);
        else if (obj->type == PLANE)
        { /*pass */ }
        else if (obj->type == CYLINDER)
        { /*pass */ }
        if (hit && temp.t < closest)
        {
            anything = 1;
            closest = temp.t;
            rec->hit = temp.hit;
            rec->normal = temp.normal;
            rec->t = temp.t;
            rec->mat = obj->mat;
        }
        ctr++;
    }
    return anything;
}

t_vec3 ftray_color(t_ray ray, t_dyn *arr, int depth)
{
    // float a;
    // t_vec3 unit_dir;
    t_hitrec rec;

    if (depth <= 0)
        return (t_vec3){0, 0, 0};

    if (!world_hit(arr, ray, 0.0001, INFINITY, &rec))
        return (ray.ambient);

    if (rec.mat->is_emitting)
        return (rec.mat->color);
    return ftvec3_plus(
        ftvec3_multiply(
            FTVEC3(clamp(rec.mat->reflectivity, 0, 1)), 
            ftray_color(ft_mat_scatter(ray, &rec), arr, depth - 1) // rework scatter... -> this should return a bool if mat scatters or not. additionaly, the color should be returned in a ptr
        ),
        ftvec3_multiply(FTVEC3(1.0-rec.mat->reflectivity), rec.mat->color)
    );
}

t_vec3 sample_square()
{
    //maybe bake array into code with offset vars
    return (t_vec3){rand_double() - .5, rand_double() - .5, 0};
    // return FTVEC3(0);
}

t_ray get_rand_ray(t_vec3 pixel_loc, t_vec3 origin, t_camera *cam)
{
    t_vec3 offset;
    t_vec3 sample_pos;

    offset = ftvec3_multiply(sample_square(), ftvec3_plus(cam->delta_u, cam->delta_v));
    sample_pos = ftvec3_plus(pixel_loc, offset);
    return ftray_create(cam->ambient, origin, ftvec3_minus(sample_pos, origin));
}

void ft_camera_apply(t_camera *cam, t_vec3 apply)
{
    cam->look_at = ftvec3_plus(cam->look_at, apply);
    ft_camera_calc(cam);
}

uint32_t ft_camera_render(
    t_app *app,
    void (*put_pixel)(mlx_image_t *image, int x, int y, uint32_t color))
{
    t_vec3 pixel00_loc;
    t_vec3 sample_scale;
    uint32_t y = 0;
    uint32_t x = 0;

    pixel00_loc = ftvec3_plus(app->active_camera->vupper_left, ftvec3_multiply(ftvec3_plus(app->active_camera->delta_u, app->active_camera->delta_v),(t_vec3){0.5,0.5,0.5}));
    sample_scale = FTVEC3(1.0 / (float) app->active_camera->samples_per_pixel);
    while (y < app->image->height)
    {
        x = 0;
        while (x < app->image->width)
        {
            t_vec3 pixel_center = ftvec3_plus(pixel00_loc, 
                ftvec3_plus(
                    ftvec3_multiply(FTVEC3(x), app->active_camera->delta_u),
                    ftvec3_multiply(FTVEC3(y), app->active_camera->delta_v)));
            t_vec3 color = FTVEC3(0);
            uint32_t i = 0;
            while (i < app->active_camera->samples_per_pixel)
            {
                t_vec3 new_col = ftray_color(get_rand_ray(pixel_center, app->active_camera->center, app->active_camera), &app->hitable, MAX_DEPTH);
                color = ftvec3_plus(color, new_col);
                // color = ftvec3_plus(color, ftvec3_divide(new_col, FTVEC3(app->active_camera->samples_per_pixel)));
                i++;
            }
            put_pixel(app->image, x, y, ftvec3_tocolor(ftvec3_multiply(color, sample_scale), 1.0));
            put_pixel(app->image, x, y, ftvec3_tocolor(ftvec3_lin_gamma(ftvec3_multiply(color, sample_scale)), 1.0));
            x++;
        }
        y++;
    }
    return (0);
}
