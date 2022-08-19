/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 23:15:02 by jkong             #+#    #+#             */
/*   Updated: 2022/08/18 15:02:23 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <math.h>

void	camera_init(t_rt_conf *conf, t_camera *out)
{
	t_vec3	orientation;
	t_vec3	horiz;
	t_vec3	vert;
	double	fd;
	t_vec3	tmp;

	orientation = conf->camera.direction;
	horiz = vec3_cross(orientation, (t_vec3){0, 1, 0});
	if (vec3_len_sq(horiz) == .0)
		horiz = vec3_cross(orientation, (t_vec3){0, 0, -1});
	vert = vec3_cross(horiz, orientation);
	fd = conf->window_size.x / tan((conf->camera.fov / 180. * M_PI) / 2);
	orientation = vec3_unit(orientation);
	horiz = vec3_unit(horiz);
	vert = vec3_unit(vert);
	tmp = conf->camera.origin;
	tmp = vec3_add(tmp, vec3_mul(fd, orientation));
	tmp = vec3_add(tmp, vec3_mul(-conf->window_size.x / 2, horiz));
	tmp = vec3_add(tmp, vec3_mul(-conf->window_size.y / 2, vert));
	out->origin = conf->camera.origin;
	out->left_top = tmp;
	out->horizontal = horiz;
	out->vertical = vert;
}

void	ray_from_camera(t_camera *cam, double x, double y, t_ray *out)
{
	t_pt3	target;

	target = cam->left_top;
	target = vec3_add(target, vec3_mul(x, cam->horizontal));
	target = vec3_add(target, vec3_mul(y, cam->vertical));
	out->origin = cam->origin;
	out->view_point = vec3_sub(target, out->origin);
	out->direction = vec3_unit(vec3_sub(target, out->origin));
	out->t_min = MIN_RAY_LENGTH;
	out->t_max = MAX_RAY_LENGTH;
	out->x = x;
	out->y = y;
}

void	ray_to_light(t_pt3 pt, t_list_light *light, t_ray *out)
{
	t_vec3	orientation;

	orientation = vec3_sub(light->origin, out->origin);
	out->origin = pt;
	out->direction = vec3_unit(orientation);
	out->t_min = MIN_RAY_LENGTH;
	out->t_max = vec3_len(orientation);
}

int	ray_try_doing_hit(t_list_object *world, t_ray *ray, t_hit *hit)
{
	t_list_object	*it;
	int				found;
	t_hit			hit_internal;

	found = 0;
	it = world;
	while (it)
	{
		if (it->on_hit(it, ray, &hit_internal))
		{
			found = 1;
			*hit = hit_internal;
			ray->t_max = hit_internal.t;
		}
		it = it->next;
	}
	return (found);
}
