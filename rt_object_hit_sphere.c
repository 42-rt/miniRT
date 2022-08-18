/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_hit_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:08:50 by jkong             #+#    #+#             */
/*   Updated: 2022/08/18 10:43:01 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	_find_solution(t_list_object *self, t_ray *ray, double *out)
{
	t_vec3	vec;
	t_vec3	second;
	double	discriminant;
	double	x;

	vec = vec3_sub(ray->origin, self->origin);
	second = (t_vec3){
		vec3_dot(ray->direction, ray->direction),
		vec3_dot(ray->direction, vec),
		vec3_dot(vec, vec) - self->width * self->width
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

int	sphere_hit(void *this_ptr, t_ray *ray, t_hit *out)
{
	t_list_object *const	self = this_ptr;
	double					t;

	if (!_find_solution(self, ray, &t))
		return (0);
	out->t = t;
	out->collision = vec3_add(ray->origin, vec3_mul(t, ray->direction));
	out->normal = vec3_div(self->width, vec3_sub(out->collision, self->origin));
	out->f = vec3_dot(ray->direction, out->normal) < 0;
	if (!out->f)
		out->normal = vec3_neg(out->normal);
	out->obj = self;
	return (1);
}
