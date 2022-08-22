/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_hit_cylinder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:08:50 by jkong             #+#    #+#             */
/*   Updated: 2022/08/22 08:34:18 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <math.h>

static t_vec3	_get_polynomial(t_list_object *self, t_ray *ray)
{
	t_vec3	v[5];

	v[0] = vec3_unit(self->direction);
	v[1] = ray->direction;
	v[2] = vec3_sub(ray->origin, self->origin);
	v[3] = vec3_sub(v[1], vec3_mul(vec3_dot(v[1], v[0]), v[0]));
	v[4] = vec3_sub(v[2], vec3_mul(vec3_dot(v[2], v[0]), v[0]));
	return ((t_vec3){
		vec3_len_sq(v[3]),
		vec3_dot(v[3], v[4]),
		vec3_len_sq(v[4]) - self->width * self->width
	});
}

static int	_find_solution(t_list_object *self, t_ray *ray, double *out)
{
	t_vec3	second;
	double	discriminant;
	double	x;

	second = _get_polynomial(self, ray);
	discriminant = second_df_half(second);
	if (discriminant < 0)
		return (0);
	x = second_qe_half(second, -discriminant);
	if (x <= ray->t_min || x >= ray->t_max)
	{
		x = second_qe_half(second, +discriminant);
		if (x <= ray->t_min || x >= ray->t_max)
			return (0);
	}
	*out = x;
	return (1);
}

static void	_apply_normal(t_list_object *self, t_hit *hit,
	t_vec3 dir, double h)
{
	t_vec3	v;
	t_vec3	vec_u;
	t_vec3	vec_v;
	t_vec3	vec_w;
	t_vec3	uvw;

	v = vec3_sub(vec3_sub(hit->collision, self->origin), vec3_mul(h, dir));
	hit->normal = vec3_div(self->width, v);
	vec_w = vec3_uv(self->direction, &vec_u, &vec_v);
	uvw.x = vec3_dot(vec_u, hit->normal);
	uvw.y = vec3_dot(vec_w, hit->normal);
	uvw.z = vec3_dot(vec_v, hit->normal);
	hit->uv = (t_vec3){
		.5 + atan2(uvw.x, uvw.z) / (2 * M_PI),
		h / self->height,
		0.
	};
}

static int	_fill_record_limit(t_list_object *self, t_ray *ray, t_hit *out)
{
	t_ray	ray_temp;
	t_vec3	dir;
	double	t;
	double	h;

	if (!_find_solution(self, ray, &t))
		return (0);
	dir = vec3_unit(self->direction);
	out->collision = vec3_add(ray->origin, vec3_mul(t, ray->direction));
	h = vec3_dot(vec3_sub(out->collision, self->origin), dir);
	if (h < 0 || h >= self->height)
	{
		ray_temp = *ray;
		ray_temp.t_min = t;
		if (!_find_solution(self, &ray_temp, &t))
			return (0);
		out->collision = vec3_add(ray->origin, vec3_mul(t, ray->direction));
		h = vec3_dot(vec3_sub(out->collision, self->origin), dir);
		if (h < 0 || h >= self->height)
			return (0);
	}
	_apply_normal(self, out, dir, h);
	out->t = t;
	return (1);
}

int	cylinder_hit(void *this_ptr, t_ray *ray, t_hit *out)
{
	t_list_object *const	self = this_ptr;

	if (_fill_record_limit(self, ray, out))
	{
		out->f = vec3_dot(ray->direction, out->normal) < 0;
		if (!out->f)
			out->normal = vec3_neg(out->normal);
		out->obj = self;
		return (1);
	}
	return (0);
}
