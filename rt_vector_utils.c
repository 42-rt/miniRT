/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:13:08 by jkong             #+#    #+#             */
/*   Updated: 2022/08/18 14:45:48 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <math.h>

t_vec3	vec3_sub(t_vec3 lhs, t_vec3 rhs)
{
	return (vec3_add(lhs, vec3_neg(rhs)));
}

t_vec3	vec3_div(double lhs, t_vec3 rhs)
{
	return (vec3_mul(1. / lhs, rhs));
}

double	vec3_len(t_vec3 vec)
{
	return (sqrt(vec3_len_sq(vec)));
}

t_vec3	vec3_unit(t_vec3 vec)
{
	return (vec3_mul(pow(vec3_len_sq(vec), -.5), vec));
}
