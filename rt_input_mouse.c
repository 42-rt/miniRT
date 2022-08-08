/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_input_mouse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:33:38 by jkong             #+#    #+#             */
/*   Updated: 2022/05/04 02:16:30 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "util_flag.h"
#include "mlxdef.h"

#include "mlx.h"

static int	_get_mouse_flag(int button)
{
	if (button == MLX_MB_LEFT)
		return (MLX_MOD_MOUSE_LEFT);
	else if (button == MLX_MB_RIGHT)
		return (MLX_MOD_MOUSE_RIGHT);
	else if (button == MLX_MB_OTHER)
		return (MLX_MOD_MOUSE_OTHER);
	return (MLX_NO_MOD);
}

static int	_on_mouse_vertical_wheel(t_rt *unit, int up)
{
	(void)&unit;
	(void)&up;
	return (1);
}

static int	_mouse_down_hook(int button, int x, int y, void *param)
{
	t_rt *const	unit = param;
	const int	flag = _get_mouse_flag(button);
	int			re;

	if (x < 0 || x >= unit->win_size_x || y < 0 || y >= unit->win_size_y)
		return (0);
	if (flag != MLX_NO_MOD)
		set_flag(&unit->input.pressed, flag);
	else
	{
		re = 0;
		if (button == MLX_MB_WHEEL_DOWN)
			re |= _on_mouse_vertical_wheel(unit, 0);
		if (button == MLX_MB_WHEEL_UP)
			re |= _on_mouse_vertical_wheel(unit, 1);
		if (re)
			unit->update_posted = 1;
	}
	return (0);
}

static int	_mouse_up_hook(int button, int x, int y, void *param)
{
	t_rt *const	unit = param;
	const int	flag = _get_mouse_flag(button);

	(void)x;
	(void)y;
	if (flag != MLX_NO_MOD)
		reset_flag(&unit->input.pressed, flag);
	return (0);
}

void	enable_mouse_hook(t_rt *unit)
{
	mlx_mouse_hook(unit->win_ptr, &_mouse_down_hook, unit);
	mlx_hook(unit->win_ptr,
		ButtonRelease, ButtonReleaseMask,
		&_mouse_up_hook, unit);
}
