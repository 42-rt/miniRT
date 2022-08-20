/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:15:51 by jkong             #+#    #+#             */
/*   Updated: 2022/08/20 14:53:02 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "safe_mem.h"
#include "safe_io.h"
#include "util_flag.h"

#include "mlx.h"

static int	_create_window(t_rt *unit, int width, int height)
{
	char *const		title = unit->conf.name;
	t_list_image	*it;

	unit->win_ptr = mlx_new_window(unit->mlx_ptr, width, height, title);
	if (!unit->win_ptr)
		return (0);
	unit->img.ptr = mlx_new_image(unit->mlx_ptr, width, height);
	if (!unit->img.ptr)
		return (0);
	unit->img.width = width;
	unit->img.height = height;
	it = unit->conf.images;
	while (it)
	{
		it->img.ptr = mlx_xpm_file_to_image(unit->mlx_ptr, it->path,
				&it->img.width, &it->img.height);
		if (!it->img.ptr)
			return (0);
		it = it->next;
	}
	camera_init(&unit->conf, &unit->camera);
	set_flag(&unit->update_posted, 1);
	set_hook(unit);
	return (1);
}

static int	_rt(void *mlx_ptr, t_rt *unit, char *path)
{
	int	width;
	int	height;

	unit->mlx_ptr = mlx_ptr;
	unit->entry = calloc_safe(1, sizeof(*unit->entry));
	if (try_eval(path, &unit->entry) && get_conf(unit->entry, &unit->conf))
	{
		width = (int)unit->conf.window_size.x;
		height = (int)unit->conf.window_size.y;
		unit->win_size_x = width;
		unit->win_size_y = height;
		if (_create_window(unit, width, height))
			return (1);
		else
			puterr_safe("MLX Error\n");
	}
	else
		puterr_safe("Error\n");
	return (0);
}

static void	_rt_destroy(t_rt *unit)
{
	t_list_image	*it;

	if (unit->img.ptr)
		mlx_destroy_image(unit->mlx_ptr, unit->img.ptr);
	it = unit->conf.images;
	while (it)
	{
		if (it->img.ptr)
			mlx_destroy_image(unit->mlx_ptr, it->img.ptr);
		it = it->next;
	}
	dispose_conf(&unit->conf);
	dispose_entry(unit->entry);
}

static void	_rt_multiple(void *mlx_ptr, int argc, int begin, char *argv[])
{
	const int			len = argc - begin;
	t_rt *const			rt_arr = calloc_safe(len, sizeof(*rt_arr));
	const t_array_rt	arr = {len, rt_arr};
	int					i;
	int					loop;

	i = 0;
	loop = 0;
	while (i < len)
	{
		loop |= _rt(mlx_ptr, &rt_arr[i], argv[begin + i]);
		i++;
	}
	if (loop)
	{
		set_global_hook(mlx_ptr, &arr);
		mlx_loop(mlx_ptr);
	}
	while (--i >= 0)
		_rt_destroy(&rt_arr[i]);
	free(rt_arr);
}

int	main(int argc, char *argv[])
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
