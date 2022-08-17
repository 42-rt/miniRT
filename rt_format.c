/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:39 by jkong             #+#    #+#             */
/*   Updated: 2022/08/17 22:22:09 by jkong            ###   ########.fr       */
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
	if (!get_child(ent, key, &ent))
		return (0);
	while (ent)
	{
		list_append((void *)out, (void *)_make_light(ent->child));
		ent = ent->next;
	}
	return (1);
}

int	get_objects(t_entry *ent, const char *key, t_list_object **out);

int	get_conf(t_entry *ent, t_rt_conf *out)
{
	t_entry	*chld;

	if (!get_string(ent, "name", &out->name))
		return (0);
	if (!get_vec2(ent, "window_size", &out->window_size))
		return (0);
	if (!get_child(ent, "ambient_lighting", &chld))
		return (0);
	if (!get_double(chld, "ratio", &out->ambient.ratio))
		return (0);
	if (!get_vec3(chld, "color", &out->ambient.color))
		return (0);
	if (!get_child(ent, "camera", &chld))
		return (0);
	if (!get_vec3(chld, "origin", &out->camera.origin))
		return (0);
	if (!get_vec3(chld, "direction", &out->camera.direction))
		return (0);
	if (!get_double(chld, "fov", &out->camera.fov))
		return (0);
	if (!_get_lights(ent, "lights", &out->lights))
		return (0);
	if (!get_objects(ent, "objects", &out->objects))
		return (0);
	return (1);
}

void	dispose_conf(t_rt_conf *in)
{
	list_walk((void *)in->lights, free_safe);
	list_walk((void *)in->objects, free_safe);
}
