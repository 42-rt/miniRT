/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_format_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:39 by jkong             #+#    #+#             */
/*   Updated: 2022/08/19 19:52:01 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "safe_mem.h"
#include "generic_list.h"

t_ray_hit_func	*on_hit_func(enum e_object_type type);

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

static void	get_material(t_entry *ent, t_material *mat)
{
	ft_memset(mat, 0, sizeof(*mat));
	mat->ra = 1.;
	mat->rd = 1.;
	mat->rs = 1.;
	mat->s = 8;
	if (!ent)
		return ;
	get_double(ent, "ambient-reflection", &mat->ra);
	get_double(ent, "diffuse-reflection", &mat->rd);
	get_double(ent, "specular-reflection", &mat->rs);
	get_double(ent, "shininess", &mat->s);
	get_int(ent, "mirror", &mat->mirror);
	get_vec3(ent, "mirror-attenuation", &mat->am);
	get_int(ent, "lens", &mat->lens);
	get_vec3(ent, "lens-attenuation", &mat->al);
	get_double(ent, "permittivity", &mat->e);
}

static t_list_object	*_make_object(enum e_object_type type, t_entry *ent)
{
	t_list_object	*elem;
	t_entry			*chld;

	elem = calloc_safe(1, sizeof(*elem));
	elem->type = type;
	elem->on_hit = on_hit_func(type);
	get_vec3(ent, "origin", &elem->origin);
	get_vec3(ent, "direction", &elem->direction);
	get_double(ent, "width", &elem->width);
	get_double(ent, "height", &elem->height);
	get_vec3(ent, "color", &elem->color);
	get_child(ent, "material", &chld);
	get_material(chld, &elem->material);
	get_int(ent, "checkerboard", &elem->checkerboard);
	return (elem);
}

int	get_objects(t_entry *ent, const char *key, t_list_object **out)
{
	char				*str;
	enum e_object_type	type;

	if (!get_child(ent, key, &ent))
		return (0);
	while (ent)
	{
		if (!get_string(ent->child, "type", &str))
			return (0);
		type = _to_object_type(str);
		if (type == OBJ_INVALID)
			return (0);
		list_append((void *)out, (void *)_make_object(type, ent->child));
		ent = ent->next;
	}
	return (1);
}
