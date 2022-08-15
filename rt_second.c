/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_second.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 18:52:19 by jkong             #+#    #+#             */
/*   Updated: 2022/08/15 00:53:03 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <math.h>

// Discriminant Function
double	second_df(t_vec3 vec)
{
	return (vec.y * vec.y - 4 * vec.x * vec.z);
}

// Discriminant Function for half b
double	second_df_half(t_vec3 vec)
{
	return (vec.y * vec.y - vec.x * vec.z);
}

// Quadratic Equation
double	second_qe(t_vec3 vec, double d)
{
	double	x;

	x = -vec.y;
	if (d < 0)
		x -= sqrt(-d);
	else if (d > 0)
		x += sqrt(d);
	x /= 2. * vec.x;
	return (x);
}

// Quadratic Equation for half b
double	second_qe_half(t_vec3 vec, double quarter_d)
{
	double	x;

	x = -vec.y;
	if (quarter_d < 0)
		x -= sqrt(-quarter_d);
	else if (quarter_d > 0)
		x += sqrt(quarter_d);
	x /= vec.x;
	return (x);
}
