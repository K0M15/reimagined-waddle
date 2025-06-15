/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftcamera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:54:06 by afelger           #+#    #+#             */
/*   Updated: 2025/06/15 11:02:54 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t ft_camera_init(
    t_camera *camera,
    t_vec3 center,
    float focal_length,
    float viewport_width,
    float viewport_height,
    int imageHeight,
    int imageWidth)
{
    camera->center = center;
    camera->focal_length = focal_length;
    camera->viewport_width = viewport_width;
    camera->viewport_height = viewport_height;
    camera->u = (t_vec3) {camera->viewport_width, 0, 0};
    camera->v = (t_vec3) {0, -camera->viewport_height, 0};
    camera->delta_u = ftvec3_divide(camera->u, (t_vec3){imageWidth, imageWidth, imageWidth});
    camera->delta_v = ftvec3_divide(camera->v, (t_vec3){imageHeight, imageHeight, imageHeight});
    return (0);
}


void ft_sphere_assign(t_obj *sphere, float radius, t_vec3 position)
{
    float *sphere_r;
    t_vec3 *sphere_pos;

    sphere_r = sphere->props;
    sphere_pos = sphere->props + sizeof(float);
    *sphere_r = radius;
    sphere_pos->x = position.x;
    sphere_pos->y = position.y;
    sphere_pos->z = position.z;
}

t_obj ft_sphere_create(float radius, t_vec3 position)
{
    t_obj sphere;

    sphere.type = SPHERE;
    sphere.props = malloc(sizeof(float) + sizeof(t_vec3));
    ft_sphere_assign(&sphere, fmax(radius, 0.0), position);
    return sphere;
}

t_vec3 ft_sphere_getcenter(void *props)
{
    return *(t_vec3 *)(props + sizeof(float));
}

float ft_sphere_getradius(void *props)
{
    return *(float *)props;
}

uint32_t ft_sphere_hit(t_obj sphere, t_ray ray, double min, double max, t_hitrec *rec)
{
    t_vec3 oc;
    t_vec3 abc;
    float disciminant;
    float root;

    oc = ftvec3_minus(ft_sphere_getcenter(sphere.props), ray.origin);
    abc = (t_vec3) {
        ftvec3_dot(ray.direction, ray.direction),
        ftvec3_dot(ray.direction, oc),
        ftvec3_dot(oc, oc) - ft_sphere_getradius(sphere.props) * ft_sphere_getradius(sphere.props)
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
    rec->normal = ftvec3_divide(ftvec3_minus(rec->hit, ft_sphere_getcenter(sphere.props)), FTVEC3(ft_sphere_getradius(sphere.props)));
    return true;
}

void ft_sphere_dest(t_obj sphere)
{
    free(sphere.props);
}

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
        if (hit && temp.t < closest)
        {
            anything = 1;
            closest = temp.t;
            rec->hit = temp.hit;
            rec->normal = temp.normal;
            rec->t = temp.t;
        }
        ctr++;
    }
    return anything;
}

uint32_t ftray_color(t_ray ray, t_dyn *arr)
{
    float a;
    t_vec3 unit_dir;
    t_vec3 color;
    // float hit;
    t_hitrec rec;

    if (world_hit(arr, ray, 0, INFINITY, &rec))
        return ftvec3_tocolor(ftvec3_multiply(FTVEC3(0.5), ftvec3_plus(rec.normal, FTVEC3(1))), 1);
    unit_dir = ftvec3_unit(ray.direction);
    a = 0.5 * (unit_dir.y + 1.0);
    color = ftvec3_plus(ftvec3_multiply(FTVEC3(1.0-a), FTVEC3(1.0)), ftvec3_multiply(FTVEC3(a), (t_vec3){0.5, 0.7, 1.0}));
    return ftvec3_tocolor(color, 1.0);
}

uint32_t ft_camera_render(
    t_app *app,
    int32_t (*put_pixel)(mlx_image_t *image, int x, int y, uint32_t color))
{
    t_vec3 vupper_left;
    t_vec3 pixel00_loc;
    t_vec3 pixel_center;
    t_ray ray;
    uint32_t y = 0;
    uint32_t x = 0;
    
    vupper_left = ftvec3_minus(app->active_camera->center, (t_vec3){0,0,app->active_camera->focal_length});
    vupper_left = ftvec3_minus(vupper_left, ftvec3_divide(app->active_camera->u, FTVEC3(2)));
    vupper_left = ftvec3_minus(vupper_left, ftvec3_divide(app->active_camera->v, FTVEC3(2)));
    pixel00_loc = ftvec3_plus(vupper_left, ftvec3_multiply(ftvec3_plus(app->active_camera->delta_u, app->active_camera->delta_v),(t_vec3){0.5,0.5,0.5}));

    // printf("Camera Stats:\n\tdelta_u: %.3f %.3f%.3f \n\tdelta_v: %.3f %.3f %.3f\n\tpixel_loc: %.3f %.3f %.3f\n",
    //     app->active_camera->delta_u.x, app->active_camera->delta_u.y, app->active_camera->delta_u.z,
    //     app->active_camera->delta_v.x, app->active_camera->delta_v.y, app->active_camera->delta_v.z,
    //     pixel00_loc.x, pixel00_loc.y, pixel00_loc.z);
    // printf("Image stats: Width %d, Height: %d\n", image->width, image->height);
    while (y < app->image->height)
    {
        x = 0;
        while (x < app->image->width)
        {
            pixel_center = ftvec3_plus(pixel00_loc, 
                ftvec3_plus(
                    ftvec3_multiply(FTVEC3(x), app->active_camera->delta_u),
                    ftvec3_multiply(FTVEC3(y), app->active_camera->delta_v)));
            ray = ftray_create(app->active_camera->center, ftvec3_minus(pixel_center, app->active_camera->center));
            uint32_t color = ftray_color(ray, &app->hitable);
            // if (x == 1 && y % 100 == 0)
            //     printf("R:%d G:%d B:%d\n", color >> 24, (color & 0x00FF)>> 16, (color & 0x0000FF)>> 8);
            put_pixel(app->image, x, y, color);
            x++;
        }
        y++;
    }
    return (0);
}
