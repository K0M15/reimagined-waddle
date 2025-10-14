/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftcamera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:54:06 by afelger           #+#    #+#             */
/*   Updated: 2025/10/14 14:07:26 by afelger          ###   ########.fr       */
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
    camera->viewport_u = ftvec3_multiply(camera->u, ftvec3(camera->viewport_width));
    camera->viewport_v = ftvec3_multiply(camera->v, ftvec3(camera->viewport_height));
    camera->delta_u = ftvec3_divide(camera->viewport_u, ftvec3(camera->image_width));
    camera->delta_v = ftvec3_divide(camera->viewport_v, ftvec3(camera->image_height));
    camera->vupper_left = ftvec3_minus(camera->center, ftvec3_multiply(ftvec3(camera->focal_length), camera->w));
    camera->vupper_left = ftvec3_minus(camera->vupper_left, ftvec3_divide(camera->viewport_u, ftvec3(2)));
    camera->vupper_left = ftvec3_minus(camera->vupper_left, ftvec3_divide(camera->viewport_v, ftvec3(2)));
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
    camera->ambient_intensity = props.ambient_intensity;
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
        rec->normal = ftvec3_multiply(outwar_norm, ftvec3(-1));
}

uint32_t ft_sphere_hit(t_obj sphere, t_ray ray, double min, double max, t_hitrec *rec)
{
    t_vec3 oc;
    t_vec3 abc;
    float discriminant;
    float root;

    oc = ftvec3_minus(((t_sphere_p *)sphere.props)->position, ray.origin);
    abc = (t_vec3) {
        ftvec3_dot(ray.direction, ray.direction),
        ftvec3_dot(ray.direction, oc),
        ftvec3_dot(oc, oc) - ((t_sphere_p *)sphere.props)->radius * ((t_sphere_p *)sphere.props)->radius
    };
    discriminant = (abc.y*abc.y - abc.x * abc.z);
    if (discriminant < 0)
        return 0;
    discriminant = sqrtf(discriminant);
    root = (abc.y - discriminant) / abc.x;
    if (root <= min || max <= root)
    {
        root = (abc.y + discriminant) / abc.x;
        if (root <= min || max <= root)
            return false;
    }
    rec->t = root;
    rec->hit = ftray_at(ray, root);
    ft_hitr_set_face_normal(rec, ray, ftvec3_divide(ftvec3_minus(rec->hit,((t_sphere_p *)sphere.props)->position), ftvec3(((t_sphere_p *)sphere.props)->radius)));
    return true;
}

uint32_t ft_cylinder_hit(t_obj cyl, t_ray ray, double min, double max, t_hitrec *rec)
{
    // TODO: Rework the cylinder
    t_cylinder_p *c = (t_cylinder_p *)cyl.props;
    t_vec3 axis = ftvec3_unit(c->rotation);
    t_vec3 base = c->position;
    float radius = c->radius;
    float height = c->height;
    t_vec3 ro_base = ftvec3_minus(ray.origin, base);
    float dv = ftvec3_dot(ray.direction, axis);
    t_vec3 v = ftvec3_minus(ray.direction, ftvec3_multiply(axis, ftvec3(dv)));
    float ow = ftvec3_dot(ro_base, axis);
    t_vec3 w = ftvec3_minus(ro_base, ftvec3_multiply(axis, ftvec3(ow)));

    float a = ftvec3_dot(v, v);
    float b = 2.0f * ftvec3_dot(v, w);
    float c_term = ftvec3_dot(w, w) - radius * radius;

    double best_t = INFINITY;
    t_vec3 best_hit = ftvec3(0);
    t_vec3 best_normal = ftvec3(0);

    if (fabs(a) > FLOAT_NEAR_ZERO)
    {
        float disc = b * b - 4.0f * a * c_term;
        if (disc >= 0.0f)
        {
            float sd = sqrtf(disc);
            float t0 = (-b - sd) / (2.0f * a);
            float t1 = (-b + sd) / (2.0f * a);
            float roots[2] = { t0, t1 };
            for (int ri = 0; ri < 2; ++ri)
            {
                double t = roots[ri];
                if (!(t > min && t < max))
                    continue;
                t_vec3 p = ftray_at(ray, t);
                float proj = ftvec3_dot(ftvec3_minus(p, base), axis);
                if (proj >= 0.0f - FLOAT_NEAR_ZERO && proj <= height + FLOAT_NEAR_ZERO)
                {
                    if (t < best_t)
                    {
                        best_t = t;
                        best_hit = p;
                        t_vec3 out = ftvec3_minus(ftvec3_minus(p, base), ftvec3_multiply(axis, ftvec3(proj)));
                        best_normal = ftvec3_unit(out);
                    }
                }
            }
        }
    }
    t_vec3 cap_centers[2] = { base, ftvec3_plus(base, ftvec3_multiply(axis, ftvec3(height))) };
    t_vec3 cap_normals[2] = { ftvec3_multiply(axis, ftvec3(-1.0f)), axis };
    int ci = 0;
    while (ci < 2)
    {
        t_vec3 cc = cap_centers[ci];
        t_vec3 cn = cap_normals[ci];
        float denom = ftvec3_dot(axis, ray.direction);
        if (fabs(denom) < FLOAT_NEAR_ZERO)
        {
            ci++;
            continue;
        }
        double tcap = ftvec3_dot(axis, ftvec3_minus(cc, ray.origin)) / denom;
        if (!(tcap > min && tcap < max))
        {
            ci++;
            continue;
        }
        t_vec3 pcap = ftray_at(ray, tcap);
        t_vec3 vrad = ftvec3_minus(ftvec3_minus(pcap, cc), ftvec3_multiply(axis, ftvec3(ftvec3_dot(ftvec3_minus(pcap, cc), axis))));
        float dist2 = ftvec3_dot(vrad, vrad);
        if (dist2 <= radius * radius + 1e-6f)
        {
            if (tcap < best_t)
            {
                best_t = tcap;
                best_hit = pcap;
                best_normal = cn;
            }
        }
        ci++;
    }

    if (best_t == INFINITY)
        return (false);
    rec->t = best_t;
    rec->hit = best_hit;
    rec->mat = cyl.mat;
    ft_hitr_set_face_normal(rec, ray, ftvec3_unit(best_normal));
    return (true);
}


uint32_t ft_plane_hit(t_obj plane, t_ray ray, double min, double max, t_hitrec *rec)
{
    t_plane_p *props;
    double denom;
    double D;
    
    props = (t_plane_p *)plane.props;
    denom = ftvec3_dot(ftvec3_unit(props->rotation), ray.direction);
    if (fabs(denom) < DOUBLE_NEAR_ZERO)
        return (false);
    D = ftvec3_dot(ftvec3_unit(props->rotation), props->position);
    denom = (D - ftvec3_dot(ftvec3_unit(props->rotation), ray.origin)) / denom; //saving space here, overwriting denom with distance
    if (denom < min || denom > max)
        return (false);
    rec->t = denom;
    rec->hit = ftray_at(ray, denom);
    rec->mat = plane.mat;
    ft_hitr_set_face_normal(rec, ray, ftvec3_unit(props->rotation));
    return (true);
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
    ((t_cylinder_p*) cyl.props)->rotation = ftvec3_unit(((t_cylinder_p*) cyl.props)->rotation);
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

t_obj	ft_light_create(t_point_light_p props)
{
    t_obj light;

    light.type = ERROR;
    if (!(light.props = malloc(sizeof(t_point_light_p))))
        return light;
    light.type = POINT_LIGHT;
    light.mat = NULL;
    memcpy(light.props, &props, sizeof(t_point_light_p)); //test, dont know if that is valid...
    return (light);
}

t_ray ft_mat_scatter(t_ray inc, t_hitrec *rec)
{
    (void) inc;
    t_ray out;
    out.origin = rec->hit;
    //TODO:  insert inteligent scatter logic OR delete it since only specular reflections are needed
    // THIS WORKS ONLY FOR SPHERES! Maybe add object to hitrecord
    out.ambient = ftvec3(0);
    if (rand_double() < rec->mat->scatter)
        out.direction = ftvec3_unit(ftvec3_plus(ftvec3_ronhemi(rec->normal), rec->normal));
    else
        out.direction = ftvec3_unit(ftvec3_reflect(inc.direction, rec->normal));
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
        { 
            hit = ft_plane_hit(*obj, ray, min, max, &temp);
        }
        else if (obj->type == CYLINDER)
        {
            hit = ft_cylinder_hit(*obj, ray, min, max, &temp);
        }
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

// source: https://p5js.org/reference/p5/lightFalloff/#:~:text=Reference%20lightFalloff()-,lightFalloff(),when%20the%20user%20double%2Dclicks.
float distance_col_scale(float distance)
{
    float att;
    if (distance < 1e-6f)
        distance = 1e-6f;
    att = 1.0f / (1.0f + 0.1f * distance + 0.032f * distance * distance );
    att *= 6.0f;
    return att;
}

/*
    World are all objects (maybe filter => only pls)
    Ray should be semi filled, only origin
*/
uint32_t hit_pointls(t_dyn *world, t_ray ray, double min, double max, t_vec3 *color)
{
    (void) min;
    // cast ray from hit to all pls, when not intersecting other objects, add color to rec
    uint32_t i;
    uint32_t has_hit;

    i = 0;
    has_hit = 0;
    while (i < world->filled)
    {
        t_obj *obj = world->elem + i * world->mem_size;
        if (obj->type == POINT_LIGHT)
        {
            t_hitrec temp_rec;
            ray.direction = ftvec3_normalize(ftvec3_minus(((t_point_light_p *)obj->props)->position, ray.origin));
            if (!world_hit(world, ray, ftvec3_length(ftvec3_minus(((t_point_light_p *)obj->props)->position, ray.origin)), max, &temp_rec))
            {
                has_hit++;
                *color = ftcol_add(*color, ftcol_scale(((t_point_light_p *)obj->props)->color, ((t_point_light_p *)obj->props)->brightness * 1));
            }
        }
        i++;
    }
    if (has_hit)
        *color = ftcol_scale(*color, 1 / has_hit);
    return (has_hit);
}


t_vec3 ftray_color(t_ray ray, t_dyn *arr, int depth, float left_reflect)
{
    t_hitrec rec;
    t_vec3  next_color;

    if (depth <= 0 || left_reflect < .1 || !world_hit(arr, ray, 0.0001, INFINITY, &rec))
        return ftcol_scale(ray.ambient, ray.ambient_intensity);
    if (rec.mat->is_emitting)
        return (rec.mat->color); //todo: scale
    t_vec3 view_dir = ftvec3_unit(ftvec3_multiply(ray.direction, ftvec3(-1)));
    next_color = ftray_color(ft_mat_scatter(ray, &rec), arr, depth - 1, left_reflect * rec.mat->reflectivity); 
    t_vec3 local_color = ftcol_scale(ray.ambient, ray.ambient_intensity);
    t_vec3 light_acc = ftvec3(0);
    uint32_t i = 0;
    while (i < arr->filled)
    {
        t_obj *obj = arr->elem + i * arr->mem_size;
        if (obj->type == POINT_LIGHT)
        {
            t_point_light_p *pl = (t_point_light_p *)obj->props;
            t_vec3 to_light = ftvec3_minus(pl->position, rec.hit);
            t_hitrec temp;
            if (!world_hit(arr, (t_ray){
                .origin = ftvec3_plus(rec.hit, ftvec3_multiply(rec.normal, ftvec3(FLOAT_NEAR_ZERO))),
                .direction = ftvec3_unit(to_light), .ambient = ftvec3(0), .ambient_intensity = 0
            }, 0.0001, ftvec3_length(to_light) - 1e-4, &temp))
            {
                // Lambert
                float ndotl = ftvec3_dot(rec.normal, ftvec3_unit(to_light));
                if (ndotl > 0.0f)
                    light_acc = ftcol_add(light_acc, ftcol_mult(ftcol_scale(pl->color, pl->brightness * ndotl * distance_col_scale(ftvec3_length(to_light))), rec.mat->color));
                // phong
                t_vec3 reflect_dir = ftvec3_reflect(ftvec3_multiply(ftvec3_unit(to_light), ftvec3(-1)), rec.normal);
                float rdotv = ftvec3_dot(ftvec3_unit(reflect_dir), view_dir);
                if (rdotv > 0.0f)
                    light_acc = ftcol_add(
                        light_acc,
                        ftcol_scale(pl->color, pl->brightness * powf(rdotv, PHONG_SHININESS) * rec.mat->reflectivity * distance_col_scale(ftvec3_length(to_light))));
            }
        }
        i++;
    }
    return (ftcol_add(
        ftcol_scale(
            ftcol_add(local_color, light_acc),
            1.0f - rec.mat->reflectivity),
        ftcol_scale(next_color, rec.mat->reflectivity)));
}

t_vec3 sample_square()
{
    //maybe bake array into code with offset vars
    return (t_vec3){rand_double() - .5, rand_double() - .5, 0};
    // return ftvec3(0);
}

t_ray get_rand_ray(t_vec3 pixel_loc, t_vec3 origin, t_camera *cam)
{
    t_vec3 offset;
    t_vec3 sample_pos;

    offset = ftvec3_multiply(sample_square(), ftvec3_plus(cam->delta_u, cam->delta_v));
    sample_pos = ftvec3_plus(pixel_loc, offset);
    return ftray_create(cam->ambient, cam->ambient_intensity, origin, ftvec3_minus(sample_pos, origin));
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
    sample_scale = ftvec3(1.0 / (float) app->active_camera->samples_per_pixel);
    while (y < app->image->height)
    {
        x = 0;
        while (x < app->image->width)
        {
            t_vec3 pixel_center = ftvec3_plus(pixel00_loc, 
                ftvec3_plus(
                    ftcol_scale(app->active_camera->delta_u, x),
                    ftcol_scale(app->active_camera->delta_v, y)));
            t_vec3 color = ftvec3(0);
            uint32_t i = 0;
            while (i < app->active_camera->samples_per_pixel)
            {
                t_vec3 new_col = ftray_color(get_rand_ray(pixel_center, app->active_camera->center, app->active_camera), &app->hitable, MAX_DEPTH, 1);
                // color = ftvec3_plus(color, new_col);
                color = ftvec3_plus(color, ftvec3_multiply(new_col, ftvec3(1.0f / (float) app->active_camera->samples_per_pixel)));
                i++;
            }
            // put_pixel(app->image, x, y, ftvec3_tocolor(ftvec3_lin_gamma(ftvec3_multiply(color, sample_scale)), 1.0));
            (void) sample_scale; put_pixel(app->image, x, y, ftvec3_tocolor(color, 1.0));
            x++;
        }
        y++;
    }
    return (0);
}
