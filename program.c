/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:15:51 by jkong             #+#    #+#             */
/*   Updated: 2022/08/04 13:53:32 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "util_try_atof.h"
#include "parser.h"
#include "libft.h"
#include "safe_mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int	try_eval(int fd, t_entry **out)
{
	t_parser	pst;
	char		*str;
	int			success;

	ft_memset(&pst, 0, sizeof(pst));
	parser_stack_reserve(&pst, 1);
	str = "";
	success = 1;
	while (str && (success || pst.error == PE_AGAIN))
	{
		str = get_next_line(fd);
		if (!(str && str[0] == '#'))
		{
			pst.str = str;
			pst.begin = pst.str;
			pst.error = PE_SUCCESS;
			success = parse(&pst);
		}
		free(str);
	}
	ft_memset(*out, 0, sizeof(**out));
	if (success)
		swap_ptr(out, &pst.now->entry);
	parser_stack_remove_all(&pst);
	free(pst.stack_base);
	return (success);
}

int	main0(int argc, char *argv[])
{
	int		fd;
	t_entry	*ptr;

	(void)&argc;
	(void)&argv;
	fd = open(argv[1], O_RDONLY);
	ptr = calloc_safe(1, sizeof(*ptr));
	if (try_eval(fd, &ptr))
		printf("parse success\n");
	else
		printf("parse failed\n");
	dispose_entry(ptr);
	close(fd);
	return (0);
}

int main(int argc, char *argv[])
{
	const int	result = main0(argc, argv);

	//system("leaks miniRT");
	return (result);
}
