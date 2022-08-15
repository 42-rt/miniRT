/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 07:56:32 by jkong             #+#    #+#             */
/*   Updated: 2022/08/15 00:24:53 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	vec3_neg(t_vec3 vec)
{
	return ((t_vec3){-vec.x, -vec.y, -vec.z});
}

t_vec3	vec3_add(t_vec3 lhs, t_vec3 rhs)
{
	return ((t_vec3){lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z});
}

t_vec3	vec3_mul(double lhs, t_vec3 rhs)
{
	return ((t_vec3){lhs * rhs.x, lhs * rhs.y, lhs * rhs.z});
}

t_vec3	vec3_mul_v(t_vec3 lhs, t_vec3 rhs)
{
	return ((t_vec3){lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z});
}

double	vec3_len_sq(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
