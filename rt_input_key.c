/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_input_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:32:52 by jkong             #+#    #+#             */
/*   Updated: 2022/05/04 02:16:51 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "util_flag.h"
#include "mlxdef.h"

#include "mlx.h"

static void	_on_key(t_rt *unit, int flag, int keycode)
{
	if (keycode == kVK_Escape)
	{
		exit(EXIT_SUCCESS);
		return ;
	}
	if (has_flag(flag, MLX_MOD_LCONTROL) && keycode == kVK_ANSI_C)
	{
		exit(EXIT_FAILURE);
		return ;
	}
	if (has_flag(flag, MLX_MOD_LCMD) && keycode == kVK_ANSI_C)
	{
		(void)&unit;
		unit->update_posted = 1;
	}
}

static int	_key_down_hook(int keycode, void *param)
{
	t_rt *const	unit = param;

	if (keycode > 0xFF)
	{
		keycode -= 0x100;
		if (keycode < NO_MLX_MOD_KEY)
			set_flag(&unit->input.pressed, keycode);
	}
	else
		_on_key(unit, unit->input.pressed, keycode);
	return (0);
}

static int	_key_up_hook(int keycode, void *param)
{
	t_rt *const	unit = param;

	if (keycode > 0xFF)
	{
		keycode -= 0x100;
		if (keycode < NO_MLX_MOD_KEY)
			reset_flag(&unit->input.pressed, keycode);
	}
	return (0);
}

void	enable_key_hook(t_rt *unit)
{
	mlx_hook(unit->win_ptr,
		KeyPress, KeyPressMask,
		&_key_down_hook, unit);
	mlx_key_hook(unit->win_ptr, &_key_up_hook, unit);
}
