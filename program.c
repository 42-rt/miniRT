/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:15:51 by jkong             #+#    #+#             */
/*   Updated: 2022/08/16 06:35:49 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "safe_mem.h"
#include "safe_io.h"

#include "mlx.h"

static int	_rgb_to_int(t_rgb rgb)
{
	int	r;

	r = 0;
	r <<= 8;
	r |= (int)rgb.x & 0xFF;
	r <<= 8;
	r |= (int)rgb.y & 0xFF;
	r <<= 8;
	r |= (int)rgb.z & 0xFF;
	return (r);
}

int	ray_color(t_rt *unit, t_ray *ray, int depth)
{
	t_hit	hit;

	if (depth <= 0)
		return (0);
	if (ray_try_doing_hit(unit->conf.objects, ray, &hit))
	{
		//Ambient
		//Indirect (Reflection, Refraction)
		for (t_list_light *l = unit->conf.lights; l != NULL; l = l->next)
		{
			t_ray	shadow;
			t_hit	shadow_hit;

			ray_to_light(hit.collision, l, &shadow);
			if (!ray_try_doing_hit(unit->conf.objects, &shadow, &shadow_hit))
			{
				//Diffuse
				//Specular
			}
		}
		return (_rgb_to_int(hit.obj->color));
	}
	return (0x00AACCDD);
}

static void	_draw_test(t_rt *unit)
{
	const int	width = unit->win_size_x;
	const int	height = unit->win_size_y;
	t_ray		ray;

	fill_image(unit, 0x42);
	for (int x = 0; x < width; x++)
	for (int y = 0; y < height; y++)
	{
		ray_from_camera(&unit->camera, x, y, &ray);
		int color = ray_color(unit, &ray, 10);
		put_pixel(unit, x, y, color);
	}
	refresh_window(unit);
}

static int	_create_window(t_rt *unit)
{
	const int	width = unit->win_size_x;
	const int	height = unit->win_size_y;
	char *const	title = unit->conf.name;

	unit->win_ptr = mlx_new_window(unit->mlx_ptr, width, height, title);
	if (!unit->win_ptr)
		return (0);
	unit->img_ptr = mlx_new_image(unit->mlx_ptr, width, height);
	if (!unit->img_ptr)
		return (0);
	camera_init(&unit->conf, &unit->camera);
	_draw_test(unit); //TODO: 
	set_hook(unit);
	return (1);
}

static int	_rt(void *mlx_ptr, t_rt *unit, char *path)
{
	unit->mlx_ptr = mlx_ptr;
	unit->entry = calloc_safe(1, sizeof(*unit->entry));
	if (try_eval(path, &unit->entry) && get_conf(unit->entry, &unit->conf))
	{
		unit->win_size_x = (int)unit->conf.window_size.x;
		unit->win_size_y = (int)unit->conf.window_size.y;
		if (_create_window(unit))
			return (1);
		else
			puterr_safe("MLX Error\n");
	}
	else
		puterr_safe("Error\n");
	return (0);
}

static void	_rt_multiple(void *mlx_ptr, int argc, int begin, char *argv[])
{
	t_rt	*rt_arr;
	int		i;
	int		loop;

	rt_arr = calloc_safe(argc - begin, sizeof(*rt_arr));
	i = 0;
	loop = 0;
	while (i < argc - begin)
	{
		loop |= _rt(mlx_ptr, &rt_arr[i], argv[begin + i]);
		i++;
	}
	if (loop)
		mlx_loop(mlx_ptr);
	while (--i >= 0)
	{
		if (rt_arr[i].img_ptr)
			mlx_destroy_image(rt_arr[i].mlx_ptr, rt_arr[i].img_ptr);
		dispose_conf(&rt_arr[i].conf);
		dispose_entry(rt_arr[i].entry);
	}
	free(rt_arr);
}

int	main0(int argc, char *argv[])
{
	void		*mlx_ptr;

	if (argc < 2)
	{
		putstr_safe("No Map Filename\n");
		return (EXIT_FAILURE);
	}
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (EXIT_FAILURE);
	_rt_multiple(mlx_ptr, argc, 1, argv);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	const int	result = main0(argc, argv);

	// system("leaks miniRT");
	return (result);
}
