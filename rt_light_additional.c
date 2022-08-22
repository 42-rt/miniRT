/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light_additional.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:47:11 by jkong             #+#    #+#             */
/*   Updated: 2022/08/22 11:09:05 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

#include "mlx.h"
#include <math.h>

static t_image	*_get_image(t_list_image *image_list, char *key)
{
	t_list_image	*it;

	if (key)
	{
		it = image_list;
		while (it)
		{
			if (ft_strcmp(it->key, key) == 0)
				return (&it->img);
			it = it->next;
		}
	}
	return (NULL);
}

static void	_int_to_rgb(int i, t_rgb *out)
{
	*out = (t_vec3){(i >> 16) & 0xFF, (i >> 8) & 0xFF, (i >> 0) & 0xFF};
}

void	checkerboard_color(t_list_object *obj, t_vec3 uv, t_rgb *color,
	t_list_image *image_list)
{
	t_vec3	i;
	t_vec3	f;
	t_image	*img;
	int		clr;

	f.x = modf(obj->additional.checkerboard_horizontal * uv.x, &i.x);
	f.y = modf(obj->additional.checkerboard_vertical * uv.y, &i.y);
	if (((int)i.x + (int)i.y) & 1)
		return ;
	img = _get_image(image_list, obj->additional.checkerboard_image_key);
	if (img)
	{
		i.x = img->width * f.x;
		i.y = img->height * f.y;
		if (get_pixel(img, (int)i.x, (int)i.y, &clr))
		{
			_int_to_rgb(clr, color);
			return ;
		}
	}
	uv.z = 1.;
	color->x = vec3_dot(uv, obj->additional.checkerboard_r);
	color->y = vec3_dot(uv, obj->additional.checkerboard_g);
	color->z = vec3_dot(uv, obj->additional.checkerboard_b);
}

static void	_mat3sq_transpose(const t_vec3 matrix[3], t_vec3 transposed[3])
{
	transposed[0].x = matrix[0].x;
	transposed[0].y = matrix[1].x;
	transposed[0].z = matrix[2].x;
	transposed[1].x = matrix[0].y;
	transposed[1].y = matrix[1].y;
	transposed[1].z = matrix[2].y;
	transposed[2].x = matrix[0].z;
	transposed[2].y = matrix[1].z;
	transposed[2].z = matrix[2].z;
}

void	bump_normal(t_list_object *obj, t_vec3 uv, t_vec3 *normal,
	t_list_image *image_list)
{
	t_image	*img;
	int		clr;
	t_rgb	color;
	t_vec3	matrix[3];
	t_vec3	transposed[3];

	img = _get_image(image_list, obj->additional.bumpmap_image_key);
	if (!img)
		return ;
	uv.x = img->width * modf(obj->additional.bumpmap_horizontal * uv.x, &uv.z);
	uv.y = img->height * modf(obj->additional.bumpmap_vertical * uv.y, &uv.z);
	uv.z = 0.;
	if (!get_pixel(img, (int)uv.x, (int)uv.y, &clr))
		return ;
	_int_to_rgb(clr, &color);
	color = vec3_div(255 / 2, color);
	color = (t_vec3){color.x - 1, color.y - 1, color.z - 1};
	matrix[2] = vec3_uv(*normal, &matrix[0], &matrix[1]);
	_mat3sq_transpose(matrix, transposed);
	normal->x = vec3_dot(color, transposed[0]);
	normal->y = vec3_dot(color, transposed[1]);
	normal->z = vec3_dot(color, transposed[2]);
}
