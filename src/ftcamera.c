/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftcamera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:54:06 by afelger           #+#    #+#             */
/*   Updated: 2025/10/11 10:09:18 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "assert.h"

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

uint32_t ft_cylinder_hit(t_obj cyl, t_ray ray, double min, double max, t_hitrec *rec)
{
    t_cylinder_p *cylinder = (t_cylinder_p *)cyl.props;
    t_vec3 cylinder_axis;
    t_vec3 oc;
    t_vec3 ray_cross_axis, oc_cross_axis;
    t_vec3 abc;
    float discriminant;
    float root1, root2;
    float projection1, projection2;
    bool inside_cylinder;
    
    // Get cylinder axis from rotation (assume rotation is the axis direction)
    cylinder_axis = ftvec3_unit(cylinder->rotation);
    // Vector from ray origin to cylinder base
    oc = ftvec3_minus(ray.origin, cylinder->position);
    // Calculate quadratic equation coefficients for infinite cylinder
    // We project ray direction and oc onto the plane perpendicular to cylinder axis
    ray_cross_axis = ftvec3_cross(ray.direction, cylinder_axis);
    oc_cross_axis = ftvec3_cross(oc, cylinder_axis);
    
    abc.x = ftvec3_dot(ray_cross_axis, ray_cross_axis);
    abc.y = 2.0 * ftvec3_dot(ray_cross_axis, oc_cross_axis);
    abc.z = ftvec3_dot(oc_cross_axis, oc_cross_axis) - cylinder->radius * cylinder->radius;
    
    float radial_dist_sq = ftvec3_length(ftvec3_minus(oc, ftvec3_multiply(cylinder_axis, FTVEC3(ftvec3_dot(oc, cylinder_axis))))) * ftvec3_length(ftvec3_minus(oc, ftvec3_multiply(cylinder_axis, FTVEC3(ftvec3_dot(oc, cylinder_axis)))));
    // Handle case where ray is parallel to cylinder axis
    if (fabs(abc.x) < DOUBLE_NEAR_ZERO)
    {
        // Ray is parallel to cylinder axis - either always inside or always outside radially
        if (radial_dist_sq > cylinder->radius * cylinder->radius)
            return (false); // Outside cylinder radially, no intersection
        // If inside radially, we'd need to check cap intersections, but for now skip
        return (false);
    }
    discriminant = abc.y * abc.y - 4.0 * abc.x * abc.z;
    if (discriminant < 0)
        return (false); // No intersection with infinite cylinder   
    discriminant = sqrtf(discriminant);
    root1 = (-abc.y - discriminant) / (2.0 * abc.x); // Near intersection
    root2 = (-abc.y + discriminant) / (2.0 * abc.x); // Far intersection
    // Calculate projections along cylinder axis for both intersection points
    t_vec3 hit1 = ftray_at(ray, root1);
    t_vec3 hit2 = ftray_at(ray, root2);
    projection1 = ftvec3_dot(ftvec3_minus(hit1, cylinder->position), cylinder_axis);
    projection2 = ftvec3_dot(ftvec3_minus(hit2, cylinder->position), cylinder_axis);
    
    float final_root = -1;
    t_vec3 final_hit;
    inside_cylinder = (radial_dist_sq < cylinder->radius * cylinder->radius) &&
                     (ftvec3_dot(oc, cylinder_axis) >= 0) &&
                     (ftvec3_dot(oc, cylinder_axis) <= cylinder->height);
    if (inside_cylinder)
    {
        // first valid intersection in forward direction
        if (root2 > min && root2 < max && projection2 >= 0 && projection2 <= cylinder->height)
        {
            final_root = root2;
            final_hit = hit2;
        }
        else if (root1 > min && root1 < max && projection1 >= 0 && projection1 <= cylinder->height)
        {
            final_root = root1;
            final_hit = hit1;
        }
    }
    else
    {
        // nearest valid intersection
        if (root1 > min && root1 < max && projection1 >= 0 && projection1 <= cylinder->height)
        {
            final_root = root1;
            final_hit = hit1;
        }
        else if (root2 > min && root2 < max && projection2 >= 0 && projection2 <= cylinder->height)
        {
            final_root = root2;
            final_hit = hit2;
        }
    }
    if (final_root < 0)
        // no side hit within caps; try cap intersections
    {
        // check caps: plane intersections at position (bottom) and position + axis*height (top)
        t_vec3 cap0_pos = cylinder->position;
        t_vec3 cap1_pos = ftvec3_plus(cylinder->position, ftvec3_multiply(cylinder_axis, FTVEC3(cylinder->height)));
        float tcap0 = 0;
        float tcap1 = 0;
        bool hit_cap0 = false;
        bool hit_cap1 = false;
        // intersect ray with plane of cap0
        float denom0 = ftvec3_dot(cylinder_axis, ray.direction);
        if (fabs(denom0) > 1e-6)
        {
            tcap0 = ftvec3_dot(ftvec3_minus(cap0_pos, ray.origin), cylinder_axis) / denom0;
            if (tcap0 > min && tcap0 < max)
            {
                t_vec3 p = ftray_at(ray, tcap0);
                t_vec3 d = ftvec3_minus(p, cap0_pos);
                if (ftvec3_dot(d, d) <= cylinder->radius * cylinder->radius)
                    hit_cap0 = true;
            }
        }
        // intersect ray with plane of cap1
        float denom1 = ftvec3_dot(cylinder_axis, ray.direction);
        if (fabs(denom1) > 1e-6)
        {
            tcap1 = ftvec3_dot(ftvec3_minus(cap1_pos, ray.origin), cylinder_axis) / denom1;
            if (tcap1 > min && tcap1 < max)
            {
                t_vec3 p = ftray_at(ray, tcap1);
                t_vec3 d = ftvec3_minus(p, cap1_pos);
                if (ftvec3_dot(d, d) <= cylinder->radius * cylinder->radius)
                    hit_cap1 = true;
            }
        }

        // choose nearest cap hit if any
        float chosen_t = -1;
        t_vec3 chosen_p = FTVEC3(0);
        t_vec3 chosen_normal = FTVEC3(0);
        if (hit_cap0 && hit_cap1)
        {
            if (tcap0 < tcap1)
            {
                chosen_t = tcap0;
                chosen_p = ftray_at(ray, tcap0);
                chosen_normal = ftvec3_multiply(cylinder_axis, FTVEC3(-1));
            }
            else
            {
                chosen_t = tcap1;
                chosen_p = ftray_at(ray, tcap1);
                chosen_normal = cylinder_axis;
            }
        }
        else if (hit_cap0)
        {
            chosen_t = tcap0;
            chosen_p = ftray_at(ray, tcap0);
            chosen_normal = ftvec3_multiply(cylinder_axis, FTVEC3(-1));
        }
        else if (hit_cap1)
        {
            chosen_t = tcap1;
            chosen_p = ftray_at(ray, tcap1);
            chosen_normal = cylinder_axis;
        }

        if (chosen_t > 0)
        {
            rec->t = chosen_t;
            rec->hit = chosen_p;
            ft_hitr_set_face_normal(rec, ray, chosen_normal);
            return (true);
        }

        return (false);
    }
    rec->t = final_root;
    rec->hit = final_hit;
    // Calculate normal vector (pointing outward from cylinder axis)
    ft_hitr_set_face_normal(rec, ray, ftvec3_unit(ftvec3_minus(ftvec3_minus(rec->hit, cylinder->position), ftvec3_multiply(cylinder_axis, FTVEC3(ftvec3_dot(ftvec3_minus(rec->hit, cylinder->position), cylinder_axis))))));
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

t_ray ft_mat_scatter(t_ray inc, t_hitrec *rec)
{
    (void) inc;
    t_ray out;
    out.origin = rec->hit;
    //TODO:  insert inteligent scatter logic OR delete it since only specular reflections are needed
    // THIS WORKS ONLY FOR SPHERES! Maybe add object to hitrecord
    // preserve ambient from incoming ray
    out.ambient = inc.ambient;
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
    assert(rec.mat != NULL && "Material should not be null!");
    return ftvec3_plus(
        ftvec3_multiply(
            FTVEC3(clamp(rec.mat->reflectivity, 0, 1)), // with -03 the material is null
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
            put_pixel(app->image, x, y, ftvec3_tocolor(ftvec3_lin_gamma(ftvec3_multiply(color, sample_scale)), 1.0));
            x++;
        }
        y++;
    }
    return (0);
}
