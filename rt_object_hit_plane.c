/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_hit_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:08:50 by jkong             #+#    #+#             */
/*   Updated: 2022/08/19 19:07:49 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <math.h>

static int	_find_solution(t_list_object *self, t_ray *ray, double *out)
{
	double	cosine;
	t_vec3	vec;
	double	x;

	cosine = vec3_dot(self->direction, ray->direction);
	if (cosine == 0)
		return (0);
	vec = vec3_sub(self->origin, ray->origin);
	x = vec3_dot(self->direction, vec) / cosine;
	if (x <= ray->t_min || x >= ray->t_max)
		return (0);
	*out = x;
	return (1);
}

static int	_calc_uv(t_list_object *self, t_hit *hit, t_vec3 *out)
{
	t_vec3	vec_u;
	t_vec3	vec_v;
	t_vec3	vec;
	double	x;
	double	y;

	vec3_uv(self->direction, &vec_u, &vec_v);
	vec = vec3_sub(hit->collision, self->origin);
	x = vec3_dot(vec_u, vec);
	if (self->width != 0. && (x < 0 || x >= self->width))
		return (0);
	y = vec3_dot(vec_v, vec);
	if (self->height != 0. && (y < 0 || y >= self->height))
		return (0);
	out->x = modf(x / self->width, &out->z);
	out->y = modf(y / self->height, &out->z);
	out->z = 0.;
	return (1);
}

int	plane_hit(void *this_ptr, t_ray *ray, t_hit *out)
{
	t_list_object *const	self = this_ptr;
	double					t;

	if (!_find_solution(self, ray, &t))
		return (0);
	out->t = t;
	out->collision = vec3_add(ray->origin, vec3_mul(t, ray->direction));
	out->normal = vec3_unit(self->direction);
	out->f = vec3_dot(ray->direction, out->normal) < 0;
	if (!out->f)
		out->normal = vec3_neg(out->normal);
	if (!_calc_uv(self, out, &out->uv))
		return (0);
	out->obj = self;
	return (1);
}
