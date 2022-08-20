/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_task.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:16:07 by jkong             #+#    #+#             */
/*   Updated: 2022/08/20 10:17:20 by jkong            ###   ########.fr       */
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
		put_pixel(&self->unit->img,
			i % self->size_of_line, i / self->size_of_line, color);
		pthread_mutex_unlock(self->mutex);
		i++;
	}
	return (NULL);
}

static void	_task_pool(t_rt *unit, pthread_mutex_t *mutex, t_task *pool)
{
	const int	total = unit->win_size_x * unit->win_size_y;
	int			i;

	i = 0;
	while (i < TASK_CAPACITY)
	{
		pool[i].min = total * i / TASK_CAPACITY;
		pool[i].max = total * (i + 1) / TASK_CAPACITY;
		pool[i].size_of_line = unit->win_size_x;
		pool[i].unit = unit;
		pool[i].mutex = mutex;
		if (pthread_create(&pool[i].thread, NULL, &_task, &pool[i]) != 0)
			exit(EXIT_FAILURE);
		i++;
	}
}

static void	_refresh_window(t_rt *unit)
{
	mlx_clear_window(unit->mlx_ptr, unit->win_ptr);
	mlx_put_image_to_window(unit->mlx_ptr, unit->win_ptr, unit->img.ptr, 0, 0);
}

void	run_draw_task(t_rt *unit)
{
	pthread_mutex_t	mutex;
	t_task			*pool;
	int				i;

	fill_image(&unit->img, 0x42);
	pool = calloc_safe(TASK_CAPACITY, sizeof(*pool));
	ft_memset(&mutex, 0, sizeof(mutex));
	if (pthread_mutex_init(&mutex, NULL) != 0)
		exit(EXIT_FAILURE);
	_task_pool(unit, &mutex, pool);
	i = 0;
	while (i < TASK_CAPACITY)
	{
		if (pthread_join(pool[i++].thread, NULL) != 0)
			exit(EXIT_FAILURE);
	}
	if (pthread_mutex_destroy(&mutex) != 0)
		exit(EXIT_FAILURE);
	free(pool);
	_refresh_window(unit);
}
