/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light_additional.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:47:11 by jkong             #+#    #+#             */
/*   Updated: 2022/08/20 01:26:03 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rgb	checkerboard_color(t_list_object *obj, t_vec3 uv, t_rgb color)
{
	const int	x = (int)(obj->additional.checkerboard_horizontal * uv.x);
	const int	y = (int)(obj->additional.checkerboard_vertical * uv.y);

	if ((x + y) & 1)
		return (color);
	uv.z = 1;
	color.x = vec3_dot(uv, obj->additional.checkerboard_r);
	color.y = vec3_dot(uv, obj->additional.checkerboard_g);
	color.z = vec3_dot(uv, obj->additional.checkerboard_b);
	return (color);
}

t_vec3	bump_normal(t_list_object *obj, t_vec3 uv, t_vec3 normal)
{
	t_rgb	color;
	t_vec3	matrix[3];
	t_vec3	transposed[3];

	(void)&obj;
	(void)&uv;
	//TODO: load color
	color = vec3_div(255, color);
	color.x = 2 * color.x - 1;
	color.y = 2 * color.y - 1;
	color.z = 1 - 2 * color.z;
	if (color.z > 0)
		color.z = 0;
	matrix[2] = vec3_uv(normal, &matrix[0], &matrix[1]);
	//TODO: transpose matrix
	normal.x = vec3_dot(color, transposed[0]);
	normal.y = vec3_dot(color, transposed[1]);
	normal.z = vec3_dot(color, transposed[2]);
	return (normal);
}
