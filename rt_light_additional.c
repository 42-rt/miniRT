/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light_additional.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:47:11 by jkong             #+#    #+#             */
/*   Updated: 2022/08/20 11:56:57 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

#include "mlx.h"

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

static t_image	*_get_image(t_list_image *image_list, char *key)
{
	t_list_image	*it;

	it = image_list;
	while (it)
	{
		if (ft_strcmp(it->key, key) == 0)
			return (&it->img);
		it = it->next;
	}
	return (NULL);
}

static void	_int_to_rgb(int i, t_rgb *out)
{
	out->x = (i >> 16) & 0xFF;
	out->y = (i >> 8) & 0xFF;
	out->z = (i >> 0) & 0xFF;
}

t_vec3	bump_normal(t_list_object *obj, t_vec3 uv, t_vec3 normal,
	t_list_image *image_list)
{
	t_image	*img;
	int		clr;
	t_rgb	color;
	t_vec3	matrix[3];
	t_vec3	transposed[3];

	img = _get_image(image_list, obj->additional.bumpmap_image_key);
	if (!img || !get_pixel(img,
			(int)(img->width * uv.x), (int)(img->height * uv.y), &clr))
		return (normal);
	_int_to_rgb(clr, &color);
	color = vec3_div(255, color);
	color.x = 2 * color.x - 1;
	color.y = 2 * color.y - 1;
	color.z = 1 - 2 * color.z;
	if (color.z > 0)
		color.z = 0;
	matrix[2] = vec3_uv(normal, &matrix[0], &matrix[1]);
	_mat3sq_transpose(matrix, transposed);
	normal.x = vec3_dot(color, transposed[0]);
	normal.y = vec3_dot(color, transposed[1]);
	normal.z = vec3_dot(color, transposed[2]);
	return (normal);
}
