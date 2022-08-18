/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_task.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:16:07 by jkong             #+#    #+#             */
/*   Updated: 2022/08/18 15:54:38 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "safe_mem.h"

#include "mlx.h"
#include <pthread.h>

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

static void	*_task(void *args)
{
	const t_task	*self = args;
	int				i;
	t_ray			ray;
	int				color;

	i = self->min;
	while (i < self->max)
	{
		ray_from_camera(&self->unit->camera,
			i % self->size_of_line, i / self->size_of_line, &ray);
		color = _rgb_to_int(ray_color(self->unit, &ray, RAY_DEPTH));
		pthread_mutex_lock(self->mutex);
		put_pixel(self->unit,
			i % self->size_of_line, i / self->size_of_line, color);
		pthread_mutex_unlock(self->mutex);
		i++;
	}
	return (NULL);
}

void	draw_test(t_rt *unit)
{
	pthread_mutex_t	mutex;
	t_task			*pool;
	int				i;

	fill_image(unit, 0x42);
	ft_memset(&mutex, 0, sizeof(mutex));
	pthread_mutex_init(&mutex, NULL);
	pool = calloc_safe(TASK_CAP, sizeof(*pool));
	i = 0;
	while (i < TASK_CAP)
	{
		pool[i].min = unit->win_size_x * unit->win_size_y * i / TASK_CAP;
		pool[i].max = unit->win_size_x * unit->win_size_y * (i + 1) / TASK_CAP;
		pool[i].size_of_line = unit->win_size_x;
		pool[i].unit = unit;
		pool[i].mutex = &mutex;
		pthread_create(&pool[i].thread, NULL, &_task, &pool[i]);
		i++;
	}
	i = 0;
	while (i < TASK_CAP)
		pthread_join(pool[i++].thread, NULL);
	pthread_mutex_destroy(&mutex);
	free(pool);
	refresh_window(unit);
}
