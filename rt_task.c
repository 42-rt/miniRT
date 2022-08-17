/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_task.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:16:07 by jkong             #+#    #+#             */
/*   Updated: 2022/08/17 22:34:32 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

#include "mlx.h"

static int	_rgb_to_int(t_rgb rgb)
{
	int	r;

	if (rgb.x < 0)
		rgb.x = 0;
	if (rgb.y < 0)
		rgb.y = 0;
	if (rgb.z < 0)
		rgb.z = 0;
	if (rgb.x > 255)
		rgb.x = 255;
	if (rgb.y > 255)
		rgb.y = 255;
	if (rgb.z > 255)
		rgb.z = 255;
	r = 0;
	r <<= 8;
	r |= (int)rgb.x & 0xFF;
	r <<= 8;
	r |= (int)rgb.y & 0xFF;
	r <<= 8;
	r |= (int)rgb.z & 0xFF;
	return (r);
}

void	draw_test(t_rt *unit)
{
	const int	width = unit->win_size_x;
	const int	height = unit->win_size_y;
	int			x;
	int			y;
	t_ray		ray;

	fill_image(unit, 0x42);
	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			ray_from_camera(&unit->camera, x, y, &ray);
			put_pixel(unit, x, y,
				_rgb_to_int(ray_color(unit, &ray, RAY_DEPTH)));
			y++;
		}
		x++;
	}
	refresh_window(unit);
}
