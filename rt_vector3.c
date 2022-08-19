/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 07:56:32 by jkong             #+#    #+#             */
/*   Updated: 2022/08/15 00:58:22 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <math.h>

double	vec3_dot(t_vec3 lhs, t_vec3 rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

t_vec3	vec3_cross(t_vec3 lhs, t_vec3 rhs)
{
	return ((t_vec3){
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x
	});
}

t_vec3	vec3_rotate_yaw(t_vec3 vec, double yaw)
{
	const double	x = vec.x;
	const double	y = vec.y;

	return ((t_vec3){
		x * cos(yaw) - y * sin(yaw),
		x * sin(yaw) + y * cos(yaw),
		vec.z
	});
}

t_vec3	vec3_rotate_pitch(t_vec3 vec, double pitch)
{
	const double	y = vec.y;
	const double	z = vec.z;

	return ((t_vec3){
		vec.x,
		y * cos(pitch) - z * sin(pitch),
		y * sin(pitch) + z * cos(pitch)
	});
}

t_vec3	vec3_rotate_roll(t_vec3 vec, double roll)
{
	const double	z = vec.z;
	const double	x = vec.x;

	return ((t_vec3){
		z * sin(roll) + x * cos(roll),
		vec.y,
		z * cos(roll) - x * sin(roll)
	});
}
