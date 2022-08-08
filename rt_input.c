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

#include "mlx.h"

void	enable_key_hook(t_rt *unit);
void	enable_mouse_hook(t_rt *unit);
void	enable_mouse_move_hook(t_rt *unit);

static int	_expose_hook(void *param)
{
	t_rt *const	unit = param;

	unit->update_posted = 1;
	return (0);
}

static int	_close_hook(void *param)
{
	(void)param;
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
