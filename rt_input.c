/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:43:15 by jkong             #+#    #+#             */
/*   Updated: 2022/05/04 02:17:10 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "mlxdef.h"
#include "util_flag.h"

#include "mlx.h"

void	enable_key_hook(t_rt *unit);
void	enable_mouse_hook(t_rt *unit);
void	enable_mouse_move_hook(t_rt *unit);

static int	_expose_hook(void *param)
{
	t_rt *const	unit = param;

	set_flag(&unit->update_posted, 0);
	return (0);
}

static int	_close_hook(void *param)
{
	(void)&param;
	exit(EXIT_SUCCESS);
	return (0);
}

void	set_hook(t_rt *unit)
{
	enable_key_hook(unit);
	enable_mouse_hook(unit);
	enable_mouse_move_hook(unit);
	mlx_expose_hook(unit->win_ptr, &_expose_hook, unit);
	mlx_hook(unit->win_ptr,
		DestroyNotify, 0,
		&_close_hook, unit);
}

void	run_draw_task(t_rt *unit);

static int	_loop_hook(void *param)
{
	t_array_rt *const	arr = param;
	int					i;
	t_rt				*unit;

	i = 0;
	while (i < arr->len)
	{
		unit = &arr->arr[i++];
		if (unit->update_posted)
		{
			if (has_flag(unit->update_posted, 1))
			{
				run_draw_task(unit);
				reset_flag(&unit->update_posted, 1);
			}
		}
	}
	return (0);
}

void	set_global_hook(void *mlx_ptr, const t_array_rt *arr)
{
	mlx_loop_hook(mlx_ptr, &_loop_hook, (void *)arr);
}
