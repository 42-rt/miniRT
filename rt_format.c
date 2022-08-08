/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:39 by jkong             #+#    #+#             */
/*   Updated: 2022/08/08 20:06:34 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "safe_mem.h"
#include "generic_list.h"

static int	_get_lights(t_entry *ent, const char *key, t_list_light **out)
{
	t_list_light	*elem;

	if (!get_child(ent, key, &ent))
		return (0);
	while (ent)
	{
		elem = calloc_safe(1, sizeof(*elem));
		get_vec3(ent->child, "origin", &elem->origin);
		get_double(ent->child, "bright", &elem->bright);
		get_vec3(ent->child, "color", &elem->color);
		list_append((void *)out, (void *)elem);
		ent = ent->next;
	}
	return (1);
}

static enum e_object_type	_to_object_type(const char *str)
{
	if (ft_strcmp(str, "sphere") == 0)
		return (OBJ_SPHERE);
	else if (ft_strcmp(str, "plane") == 0)
		return (OBJ_PLANE);
	else if (ft_strcmp(str, "cylinder") == 0)
		return (OBJ_CYLINDER);
	else if (ft_strcmp(str, "second-cone") == 0)
		return (OBJ_CONE);
	else if (ft_strcmp(str, "second-hyperboloid") == 0)
		return (OBJ_HYPERBOLOID);
	else if (ft_strcmp(str, "second-paraboloid") == 0)
		return (OBJ_PARABOLOID);
	else
		return (OBJ_INVALID);
}

static int	_get_objects(t_entry *ent, const char *key, t_list_object **out)
{
	char				*str;
	enum e_object_type	type;
	t_list_object		*elem;

	if (!get_child(ent, key, &ent))
		return (0);
	while (ent)
	{
		if (!get_string(ent->child, "type", &str))
			return (0);
		type = _to_object_type(str);
		if (type == OBJ_INVALID)
			return (0);
		elem = calloc_safe(1, sizeof(*elem));
		elem->type = type;
		get_vec3(ent->child, "origin", &elem->origin);
		get_vec3(ent->child, "direction", &elem->direction);
		get_double(ent->child, "width", &elem->width);
		get_double(ent->child, "height", &elem->height);
		get_vec3(ent->child, "color", &elem->color);
		list_append((void *)out, (void *)elem);
		ent = ent->next;
	}
	return (1);
}

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
	if (!_get_objects(ent, "objects", &out->objects))
		return (0);
	return (1);
}

void	dispose_conf(t_rt_conf *in)
{
	list_walk((void *)in->lights, free_safe);
	list_walk((void *)in->objects, free_safe);
}
