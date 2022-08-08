/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:46:10 by jkong             #+#    #+#             */
/*   Updated: 2022/08/08 21:07:19 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>

int	try_eval(char *path, t_entry **out)
{
	t_parser	pst;
	char		*str;
	int			success;
	int			fd;

	fd = open(path, O_RDONLY);
	ft_memset(&pst, 0, sizeof(pst));
	parser_stack_reserve(&pst, 1);
	str = "";
	success = 1;
	while (str && (success || pst.error == PE_AGAIN))
	{
		str = get_next_line(fd);
		pst.str = str;
		pst.begin = pst.str;
		pst.error = PE_SUCCESS;
		success = parse(&pst);
		free(str);
	}
	if (success)
		swap_ptr(out, &pst.now->entry);
	parser_stack_remove_all(&pst);
	free(pst.stack_base);
	close(fd);
	return (success);
}
