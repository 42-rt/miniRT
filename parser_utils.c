/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/08/19 14:28:46 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "safe_mem.h"
#include "libft.h"

char	*get_token_str(t_token_kind token)
{
	if (token == TK_PAREN_L)
		return ("{");
	else if (token == TK_PAREN_R)
		return ("}");
	else if (token == TK_WORD)
		return ("word");
	else if (token == TK_EOF)
		return ("eof");
	return ("unknown");
}

void	swap_ptr(void *a, void *b)
{
	void	*x;

	x = *(void **)a;
	*(void **)a = *(void **)b;
	*(void **)b = x;
}

void	clear_parser_stack_item(t_parser_stack *item)
{
	free(item->word);
	dispose_entry(item->entry);
}

void	parser_stack_reserve(t_parser *pst, size_t n)
{
	size_t			capacity;
	t_parser_stack	*attach;
	t_parser_stack	*detach;
	size_t			length;

	capacity = pst->stack_capacity;
	if (capacity == 0)
		capacity = 1;
	length = (size_t)(pst->now - pst->stack_base) + 1;
	while (capacity < length + n)
		capacity <<= 1;
	if (capacity == pst->stack_capacity)
		return ;
	attach = calloc_safe(capacity, sizeof(*pst->stack_base));
	detach = pst->stack_base;
	ft_memcpy(attach, detach, pst->stack_capacity * sizeof(*pst->stack_base));
	pst->stack_base = attach;
	free(detach);
	pst->stack_capacity = capacity;
	pst->now = pst->stack_base + length - 1;
}

void	parser_stack_remove_all(t_parser *pst)
{
	while (pst->now > pst->stack_base)
		clear_parser_stack_item(pst->now--);
}
