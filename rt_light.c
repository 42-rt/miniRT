/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 23:15:02 by jkong             #+#    #+#             */
/*   Updated: 2022/08/17 16:54:55 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <math.h>

// TODO: Reflection, Refraction ... ray_color(unit, next_ray, depth - 1);
static t_vec3	_get_ambient(t_rt *unit, t_ray *ray, t_hit *hit, int depth)
{
	t_rgb	color;
	t_vec3	amb;

	(void)&ray;
	(void)&depth;
	color = hit->obj->color;
	amb = vec3_div(255 / unit->conf.ambient.ratio, unit->conf.ambient.color);
	color = vec3_mul_v(amb, color);
	return (color);
}

static t_vec3	_get_diffuse(t_list_light *l, t_hit *hit, t_ray *shadow)
{
	double	diffuse;

	diffuse = vec3_dot(shadow->direction, hit->normal);
	if (diffuse > 0)
		return (vec3_mul(l->bright * diffuse, l->color));
	return ((t_rgb){0., 0., 0.});
}

//TODO: alpha = 32 to config
static t_vec3	_get_specular(t_list_light *l, t_ray *ray,
	t_hit *hit, t_ray *shadow)
{
	double	alpha;
	double	specular;
	t_vec3	reflect;

	reflect = vec3_sub(
			vec3_mul(2 * vec3_dot(shadow->direction, hit->normal), hit->normal),
			shadow->direction);
	specular = vec3_dot(reflect, vec3_neg(ray->direction));
	if (specular > 0)
	{
		alpha = 32;
		specular = pow(specular, alpha);
		return (vec3_mul(l->bright * specular, l->color));
	}
	return ((t_rgb){0., 0., 0.});
}

t_vec3	ray_color(t_rt *unit, t_ray *ray, int depth)
{
	t_hit			hit;
	t_rgb			color;
	t_list_light	*it;
	t_ray			shadow;
	t_hit			shadow_hit;

	if (depth <= 0)
		return ((t_vec3){0., 0., 0.});
	if (ray_try_doing_hit(unit->conf.objects, ray, &hit))
	{
		color = _get_ambient(unit, ray, &hit, depth);
		it = unit->conf.lights;
		while (it)
		{
			ray_to_light(hit.collision, it, &shadow);
			if (!ray_try_doing_hit(unit->conf.objects, &shadow, &shadow_hit))
			{
				color = vec3_add(color, _get_diffuse(it, &hit, &shadow));
				color = vec3_add(color, _get_specular(it, ray, &hit, &shadow));
			}
			it = it->next;
		}
		return (color);
	}
	return ((t_vec3){255 * 0.5, 255 * 0.6, 255 * 0.8});
}
