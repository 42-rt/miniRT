/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:39 by jkong             #+#    #+#             */
/*   Updated: 2022/08/18 10:58:16 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "util_try_atoi.h"
#include "util_try_atof.h"

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

int	get_string(t_entry *ent, const char *key, char **out)
{
	if (get_child(ent, key, &ent))
	{
		*out = ent->value;
		return (1);
	}
	return (0);
}

int	get_int(t_entry *ent, const char *key, int *out)
{
	if (get_child(ent, key, &ent))
		return (try_atoi(ent->value, out));
	return (0);
}

int	get_double(t_entry *ent, const char *key, double *out)
{
	if (get_child(ent, key, &ent))
		return (try_atof(ent->value, out));
	return (0);
}
