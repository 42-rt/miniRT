/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 07:56:32 by jkong             #+#    #+#             */
/*   Updated: 2022/08/09 16:53:22 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_vec3	vec3_neg(t_vec3 vec)
{
	return ((t_vec3){-vec.x, -vec.y, -vec.z});
}

double	vec3_length(t_vec3 lhs, t_vec3 rhs)
{
	const double	dx = lhs.x - rhs.x;
	const double	dy = lhs.y - rhs.y;
	const double	dz = lhs.z - rhs.z;

	return (sqrt(dx * dx + dy * dy + dz * dz));
}

t_vec3	vec3_add(t_vec3 lhs, t_vec3 rhs)
{
	return ((t_vec3){lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z});
}

t_vec3	vec3_multiple(double lhs, t_vec3 rhs)
{
	return ((t_vec3){lhs * rhs.x, lhs * rhs.y, lhs * rhs.z});
}

double	vec3_product(t_vec3 lhs, t_vec3 rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}
