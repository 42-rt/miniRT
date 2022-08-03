/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/08/03 20:05:50 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "safe_mem.h"
#include "libft.h"

t_entry	*make_entry(void)
{
	return (calloc_safe(1, sizeof(t_entry)));
}

void	dispose_entry(t_entry *item)
{
	if (item)
	{
		free(item->value);
		dispose_entry(item->child);
		dispose_entry(item->next);
	}
	free(item);
}
