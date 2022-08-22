/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_hit_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:08:50 by jkong             #+#    #+#             */
/*   Updated: 2022/08/22 07:49:04 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <math.h>

static int	_find_solution(t_list_object *self, t_ray *ray, double *out)
{
	t_vec3	vec;
	t_vec3	second;
	double	discriminant;
	double	x;

	vec = vec3_sub(ray->origin, self->origin);
	second = (t_vec3){
		vec3_len_sq(ray->direction),
		vec3_dot(ray->direction, vec),
		vec3_len_sq(vec) - self->width * self->width
	};
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

static void	_calc_uv(t_list_object *self, t_vec3 normal, t_vec3 *out)
{
	t_vec3	vec_u;
	t_vec3	vec_v;
	t_vec3	vec_w;
	t_vec3	uvw;

	vec_w = vec3_uv(self->direction, &vec_u, &vec_v);
	uvw.x = vec3_dot(vec_u, normal);
	uvw.y = vec3_dot(vec_w, normal);
	uvw.z = vec3_dot(vec_v, normal);
	*out = (t_vec3){
		.5 + atan2(uvw.x, uvw.z) / (2 * M_PI),
		.5 + asin(uvw.y) / M_PI,
		0.
	};
}

int	sphere_hit(void *this_ptr, t_ray *ray, t_hit *out)
{
	t_list_object *const	self = this_ptr;
	double					t;
	t_vec3					vec;

	if (!_find_solution(self, ray, &t))
		return (0);
	out->t = t;
	out->collision = vec3_add(ray->origin, vec3_mul(t, ray->direction));
	vec = vec3_div(self->width, vec3_sub(out->collision, self->origin));
	out->normal = vec;
	out->f = vec3_dot(ray->direction, out->normal) < 0;
	if (!out->f)
		out->normal = vec3_neg(out->normal);
	_calc_uv(self, vec, &out->uv);
	out->obj = self;
	return (1);
}
