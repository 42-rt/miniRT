/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:15:51 by jkong             #+#    #+#             */
/*   Updated: 2022/08/03 20:18:13 by jkong            ###   ########.fr       */
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

int	try_eval(char *str, t_entry **out)
{
	t_parser	pst;
	int			success;

	ft_memset(&pst, 0, sizeof(pst));
	parser_stack_reserve(&pst, 1);
	pst.error = PE_SUCCESS;
	success = 1;
	pst.str = str;
	pst.begin = pst.str;
	success = parse(&pst);
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
	if (try_eval("text { text { text } text } text", &ptr))
	{
		printf("parse success\n");
		dispose_entry(ptr);
	}
	else
		printf("parse failed\n");
	return (0);
}

int main(int argc, char *argv[])
{
	const int	result = main0(argc, argv);

	system("leaks miniRT");
	return (result);
}
