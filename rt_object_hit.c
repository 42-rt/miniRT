/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_hit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:08:50 by jkong             #+#    #+#             */
/*   Updated: 2022/08/17 11:08:00 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	sphere_hit(void *self, t_ray *ray, t_hit *out);
int	plane_hit(void *this_ptr, t_ray *ray, t_hit *out);
int	cylinder_hit(void *this_ptr, t_ray *ray, t_hit *out);
int	cone_hit(void *this_ptr, t_ray *ray, t_hit *out);

static int	_invalid_hit(void *self, t_ray *ray, t_hit *out)
{
	(void)&self;
	(void)&ray;
	(void)&out;
	return (0);
}

t_ray_hit_func	*on_hit_func(enum e_object_type type)
{
	if (type == OBJ_SPHERE)
		return (&sphere_hit);
	else if (type == OBJ_PLANE)
		return (&plane_hit);
	else if (type == OBJ_CYLINDER)
		return (&cylinder_hit);
	else if (type == OBJ_CONE)
		return (&cone_hit);
	else if (type == OBJ_HYPERBOLOID)
		return (&_invalid_hit);
	else if (type == OBJ_PARABOLOID)
		return (&_invalid_hit);
	return (&_invalid_hit);
}
