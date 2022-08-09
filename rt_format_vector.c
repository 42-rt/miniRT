/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_format_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:39 by jkong             #+#    #+#             */
/*   Updated: 2022/08/09 17:33:16 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "util_try_atof.h"

int	get_vec2(t_entry *ent, const char *key, t_vec3 *out)
{
	if (!get_child(ent, key, &ent))
		return (0);
	if (!ent->next)
		return (0);
	if (!try_atof(ent->value, &out->x))
		return (0);
	if (!try_atof(ent->next->value, &out->y))
		return (0);
	out->z = 0.;
	return (1);
}

int	get_vec3(t_entry *ent, const char *key, t_vec3 *out)
{
	if (!get_child(ent, key, &ent))
		return (0);
	if (!ent->next || !ent->next->next)
		return (0);
	if (!try_atof(ent->value, &out->x))
		return (0);
	if (!try_atof(ent->next->value, &out->y))
		return (0);
	if (!try_atof(ent->next->next->value, &out->z))
		return (0);
	return (1);
}
