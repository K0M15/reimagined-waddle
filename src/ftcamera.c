/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftcamera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:54:06 by afelger           #+#    #+#             */
/*   Updated: 2025/06/14 15:11:02 by afelger          ###   ########.fr       */
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

uint32_t ft_camera_render(
    t_camera *camera,
    mlx_image_t *image,
    int32_t (*put_pixel)(mlx_image_t *image, int x, int y, uint32_t color))
{
    t_vec3 vupper_left;
    t_vec3 pixel00_loc;
    t_vec3 pixel_center;
    t_ray ray;
    uint32_t y = 0;
    uint32_t x = 0;
    
    vupper_left = ftvec3_minus(camera->center, (t_vec3){0,0,camera->focal_length});
    vupper_left = ftvec3_minus(vupper_left, ftvec3_divide(camera->u, FTVEC3(2)));
    vupper_left = ftvec3_minus(vupper_left, ftvec3_divide(camera->v, FTVEC3(2)));
    pixel00_loc = ftvec3_plus(vupper_left, ftvec3_multiply(ftvec3_plus(camera->delta_u, camera->delta_v),(t_vec3){0.5,0.5,0.5}));

    // printf("Camera Stats:\n\tdelta_u: %.3f %.3f%.3f \n\tdelta_v: %.3f %.3f %.3f\n\tpixel_loc: %.3f %.3f %.3f\n",
    //     camera->delta_u.x, camera->delta_u.y, camera->delta_u.z,
    //     camera->delta_v.x, camera->delta_v.y, camera->delta_v.z,
    //     pixel00_loc.x, pixel00_loc.y, pixel00_loc.z);
    // printf("Image stats: Width %d, Height: %d\n", image->width, image->height);
    while (y < image->height)
    {
        x = 0;
        while (x < image->width)
        {
            pixel_center = ftvec3_plus(pixel00_loc, 
                ftvec3_plus(
                    ftvec3_multiply(FTVEC3(x), camera->delta_u),
                    ftvec3_multiply(FTVEC3(y), camera->delta_v)));
            ray = ftray_create(camera->center, ftvec3_minus(pixel_center, camera->center));
            uint32_t color = ftray_color(ray);
            // if (x == 1 && y % 100 == 0)
            //     printf("R:%d G:%d B:%d\n", color >> 24, (color & 0x00FF)>> 16, (color & 0x0000FF)>> 8);
            put_pixel(image, x, y, color);
            x++;
        }
        y++;
    }
    return (0);
}
