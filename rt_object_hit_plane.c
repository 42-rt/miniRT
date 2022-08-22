/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_hit_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:08:50 by jkong             #+#    #+#             */
/*   Updated: 2022/08/22 11:31:26 by jkong            ###   ########.fr       */
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

static int	_retrieve_size(t_list_object *self, t_vec3 *uv, double size[2])
{
	size[0] = self->width;
	size[1] = self->height;
	if (size[0] != 0. && size[1] != 0.)
	{
		if (uv->x < 0 || uv->x >= self->width
			|| uv->y < 0 || uv->y >= self->height)
			return (0);
	}
	else if (size[0] != 0.)
	{
		if (uv->x * uv->x + uv->y * uv->y > self->width)
			return (0);
		size[1] = self->width;
	}
	else if (size[1] != 0.)
		size[0] = self->height;
	else
	{
		size[0] = DEFAULT_SIZE;
		size[1] = DEFAULT_SIZE;
	}
	return (1);
}

static int	_calc_uv_limit(t_list_object *self, t_hit *hit, t_vec3 *out)
{
	t_vec3	vec_u;
	t_vec3	vec_v;
	t_vec3	vec;
	double	size[2];

	vec3_uv(self->direction, &vec_u, &vec_v);
	vec = vec3_sub(hit->collision, self->origin);
	out->x = vec3_dot(vec_u, vec);
	out->y = vec3_dot(vec_v, vec);
	if (!_retrieve_size(self, out, size))
		return (0);
	out->x /= size[0];
	out->y /= size[1];
	out->x -= floor(out->x);
	out->y -= floor(out->y);
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
	if (!_calc_uv_limit(self, out, &out->uv))
		return (0);
	out->obj = self;
	return (1);
}
