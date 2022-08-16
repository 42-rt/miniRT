/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_hit_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:08:50 by jkong             #+#    #+#             */
/*   Updated: 2022/08/16 15:16:40 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	if (x < ray->t_min || x >= ray->t_max)
		return (0);
	*out = x;
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
	out->normal = self->direction;
	if (!(vec3_dot(ray->direction, out->normal) < 0))
		out->normal = vec3_neg(out->normal);
	out->obj = self;
	return (1);
}
