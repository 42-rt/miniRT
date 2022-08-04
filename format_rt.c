/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:39 by jkong             #+#    #+#             */
/*   Updated: 2022/08/05 02:46:31 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"
#include "libft.h"

t_entry	*get_child(t_entry *parent, const char *key, t_entry **out)
{
	while (parent)
	{
		if (ft_strcmp(parent->value, key) == 0)
		{
			if (out)
				*out = parent->child;
			return (parent->child);
		}
		parent = parent->next;
	}
	if (out)
		*out = NULL;
	return (NULL);
}

int	get_string(t_entry *it, char **out)
{
	return (1);
}

int	get_int(t_entry *it, int *out)
{
	return (1);
}

int	get_double(t_entry *it, double *out)
{
	return (1);
}

int	get_vec2(t_entry *it, t_vec2 *out)
{
	return (1);
}

int	get_vec3(t_entry *it, t_vec3 *out)
{
	return (1);
}

static int	_get_lights(t_entry *entry, t_list_light **out)
{
	return (1);
}

static int	_get_objects(t_entry *entry)
{
	return (1);
}

int	get_conf(t_entry *entry, t_rt_conf *out)
{
	t_entry	*child;

	if (!get_string(get_child(entry, "name", NULL), &out->name))
		return (0);
	if (!get_vec2(get_child(entry, "window_size", NULL), &out->window_size))
		return (0);
	if (!get_child(entry, "ambient_lighting", &child))
		return (0);
	if (!get_double(get_child(child, "ratio", NULL), &out->ambient.ratio))
		return (0);
	if (!get_vec3(get_child(child, "color", NULL), &out->ambient.color))
		return (0);
	if (!get_child(entry, "camera", &child))
		return (0);
	if (!get_vec3(get_child(child, "origin", NULL), &out->camera.origin))
		return (0);
	if (!get_vec3(get_child(child, "direction", NULL), &out->camera.direction))
		return (0);
	if (!get_double(get_child(child, "fov", NULL), &out->camera.fov))
		return (0);
	if (!_get_lights(get_child(entry, "lights", NULL), &out->lights))
		return (0);
	if (!_get_objects(get_child(entry, "objects", NULL), &out->objects))
		return (0);
	return (1);
}
