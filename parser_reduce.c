/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reduce.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/08/03 20:05:34 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

// S -> list
t_token_kind	parser_reduce_0(t_parser *pst)
{
	(void)&pst;
	return (TK_NT_ACCEPT);
}

// elem -> text
t_token_kind	parser_reduce_1(t_parser *pst)
{
	t_parser_stack	val;

	ft_memset(&val, 0, sizeof(val));
	val.entry = make_entry();
	swap_ptr(&val.entry->value, &pst->now[-0].word);
	clear_parser_stack_item(&pst->now[-0]);
	pst->now -= 1;
	*++pst->now = val;
	return (TK_NT_ELEMENT);
}

// elem -> text { list }
t_token_kind	parser_reduce_2(t_parser *pst)
{
	t_parser_stack	val;

	ft_memset(&val, 0, sizeof(val));
	val.entry = make_entry();
	swap_ptr(&val.entry->value, &pst->now[-3].word);
	swap_ptr(&val.entry->child, &pst->now[-1].entry);
	clear_parser_stack_item(&pst->now[-3]);
	clear_parser_stack_item(&pst->now[-2]);
	clear_parser_stack_item(&pst->now[-1]);
	clear_parser_stack_item(&pst->now[-0]);
	pst->now -= 4;
	*++pst->now = val;
	return (TK_NT_ELEMENT);
}

// list -> elem
t_token_kind	parser_reduce_3(t_parser *pst)
{
	(void)&pst;
	return (TK_NT_LIST);
}

// list -> list elem
t_token_kind	parser_reduce_4(t_parser *pst)
{
	t_parser_stack	val;
	t_entry			*last;

	ft_memset(&val, 0, sizeof(val));
	swap_ptr(&val.entry, &pst->now[-1].entry);
	last = val.entry;
	while (last->next)
		last = last->next;
	swap_ptr(&last->next, &pst->now[-0].entry);
	clear_parser_stack_item(&pst->now[-1]);
	clear_parser_stack_item(&pst->now[-0]);
	pst->now -= 2;
	*++pst->now = val;
	return (TK_NT_LIST);
}
