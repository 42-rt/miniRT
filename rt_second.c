/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_second.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 18:52:19 by jkong             #+#    #+#             */
/*   Updated: 2022/08/11 22:04:44 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

// Discriminant Function
double	second_df(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

// Discriminant Function for half b
double	second_df_half(double a, double half_b, double c)
{
	return (half_b * half_b - a * c);
}

// Quadratic Equation
double	second_qe(double a, double b, double c, double d)
{
	double	x;

	x = -b;
	if (d < 0)
		x -= sqrt(-d);
	else if (d > 0)
		x += sqrt(d);
	if (a != 1.)
		x /= 2. * a;
	else
		x /= 2.;
	return (x);
}

// Quadratic Equation for half b
double	second_qe_half(double a, double half_b, double c, double quarter_d)
{
	double	x;

	x = -half_b;
	if (quarter_d < 0)
		x -= sqrt(-quarter_d);
	else if (quarter_d > 0)
		x += sqrt(quarter_d);
	if (a != 1.)
		x /= a;
	return (x);
}
