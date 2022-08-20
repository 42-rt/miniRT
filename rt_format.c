/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:39 by jkong             #+#    #+#             */
/*   Updated: 2022/08/20 12:13:41 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "safe_mem.h"
#include "generic_list.h"

static t_list_light	*_make_light(t_entry *ent)
{
	t_list_light	*elem;

	elem = calloc_safe(1, sizeof(*elem));
	get_vec3(ent, "origin", &elem->origin);
	get_double(ent, "bright", &elem->bright);
	get_vec3(ent, "color", &elem->color);
	return (elem);
}

static int	_get_lights(t_entry *ent, const char *key, t_list_light **out)
{
	if (get_child(ent, key, &ent))
	{
		while (ent)
		{
			list_append((void *)out, (void *)_make_light(ent->child));
			ent = ent->next;
		}
	}
	return (1);
}

int	get_objects(t_entry *ent, const char *key, t_list_object **out);

static int	_get_images(t_entry *ent, const char *key, t_list_image **out)
{
	t_list_image	*elem;
	t_list_image	temp;

	if (get_child(ent, key, &ent))
	{
		ft_memset(&temp, 0, sizeof(temp));
		while (ent)
		{
			temp.key = ent->value;
			get_string(ent, temp.key, &temp.path);
			if (temp.path)
			{
				elem = malloc_safe(sizeof(*elem));
				*elem = temp;
				list_append((void *)out, (void *)elem);
			}
			ent = ent->next;
		}
	}
	return (1);
}

int	get_conf(t_entry *ent, t_rt_conf *out)
{
	t_entry	*chld;

	return (get_string(ent, "name", &out->name)
		&& get_vec2(ent, "window_size", &out->window_size)
		&& get_child(ent, "ambient_lighting", &chld)
		&& get_double(chld, "ratio", &out->ambient.ratio)
		&& get_vec3(chld, "color", &out->ambient.color)
		&& get_child(ent, "camera", &chld)
		&& get_vec3(chld, "origin", &out->camera.origin)
		&& get_vec3(chld, "direction", &out->camera.direction)
		&& get_double(chld, "fov", &out->camera.fov)
		&& _get_lights(ent, "lights", &out->lights)
		&& get_objects(ent, "objects", &out->objects)
		&& _get_images(ent, "images", &out->images));
}

void	dispose_conf(t_rt_conf *in)
{
	list_walk((void *)in->lights, free_safe);
	list_walk((void *)in->objects, free_safe);
}
