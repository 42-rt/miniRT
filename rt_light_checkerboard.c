/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light_checkerboard.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:47:11 by jkong             #+#    #+#             */
/*   Updated: 2022/08/19 19:55:32 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//TODO: checkerboard detail
t_rgb	checkerboard_color(t_list_object *obj, t_vec3 uv, t_rgb color)
{
	if (((int)(obj->checkerboard * uv.x) + (int)(obj->checkerboard * uv.y)) & 1)
		return ((t_rgb){255 - color.x, 255 - color.y, 255 - color.z});
	return (color);
}
