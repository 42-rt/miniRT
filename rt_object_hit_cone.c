/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_hit_cone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:08:50 by jkong             #+#    #+#             */
/*   Updated: 2022/08/18 10:42:38 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vec3	_get_polynomial(t_list_object *self, t_ray *ray)
{
	t_vec3	v[5];
	double	w_sq;
	double	h_sq;
	double	cos_sq;
	double	sin_sq;

	v[0] = self->direction;
	v[1] = ray->direction;
	v[2] = vec3_sub(ray->origin, self->origin);
	v[3] = vec3_sub(v[1], vec3_mul(vec3_dot(v[1], v[0]), v[0]));
	v[4] = vec3_sub(v[2], vec3_mul(vec3_dot(v[2], v[0]), v[0]));
	w_sq = self->width * self->width;
	h_sq = self->height * self->height;
	cos_sq = h_sq / (w_sq + h_sq);
	sin_sq = w_sq / (w_sq + h_sq);
	return ((t_vec3){
		cos_sq * vec3_dot(v[3], v[3])
		- sin_sq * vec3_dot(v[1], v[0]) * vec3_dot(v[1], v[0]),
		cos_sq * vec3_dot(v[3], v[4])
		- sin_sq * vec3_dot(v[1], v[0]) * vec3_dot(v[2], v[0]),
		cos_sq * vec3_dot(v[4], v[4])
		- sin_sq * vec3_dot(v[2], v[0]) * vec3_dot(v[2], v[0])
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

static t_vec3	_get_normal(t_list_object *self, t_hit *hit, t_vec3 d, double h)
{
	t_vec3	v;
	double	x;
	double	y;

	x = self->width;
	y = self->height;
	v = vec3_mul(h + h * x * x / y / y, d);
	return (vec3_unit(vec3_sub(vec3_sub(hit->collision, self->origin), v)));
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
	out->normal = _get_normal(self, out, dir, h);
	out->t = t;
	return (1);
}

int	cone_hit(void *this_ptr, t_ray *ray, t_hit *out)
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
