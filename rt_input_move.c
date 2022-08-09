/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_input_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:42:40 by jkong             #+#    #+#             */
/*   Updated: 2022/05/04 02:17:04 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "util_flag.h"
#include "mlxdef.h"

#include "mlx.h"
#include <math.h>

static int	_on_mouse_left(t_rt *unit, int delta_x, int delta_y)
{
	(void)&unit;
	(void)&delta_x;
	(void)&delta_y;
	return (1);
}

static int	_on_mouse_other(t_rt *unit, int delta_x, int delta_y)
{
	(void)&unit;
	(void)&delta_x;
	(void)&delta_y;
	return (1);
}

static int	_on_mouse_right(t_rt *unit, int delta_x, int delta_y)
{
	(void)&unit;
	(void)&delta_x;
	(void)&delta_y;
	return (1);
}

static int	_mouse_move_hook(int x, int y, void *param)
{
	t_rt *const	unit = param;
	const int	latest_x = unit->input.latest_x;
	const int	latest_y = unit->input.latest_y;
	int			re;

	re = 0;
	if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_LEFT))
		re |= _on_mouse_left(unit, x - latest_x, y - latest_y);
	if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_OTHER))
		re |= _on_mouse_other(unit, x - latest_x, y - latest_y);
	if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_RIGHT))
		re |= _on_mouse_right(unit, x - latest_x, y - latest_y);
	if (re)
		unit->update_posted = 1;
	unit->input.latest_x = x;
	unit->input.latest_y = y;
	return (0);
}

void	enable_mouse_move_hook(t_rt *unit)
{
	mlx_hook(unit->win_ptr,
		MotionNotify, PointerMotionMask,
		&_mouse_move_hook, unit);
}
