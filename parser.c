/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:18:56 by jkong             #+#    #+#             */
/*   Updated: 2022/08/03 22:08:15 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// S -> list
// elem -> text
// elem -> text { list }
// list -> elem
// list -> list elem
static t_parse_func *const	g_grammer[] = {
	parser_reduce_0,
	parser_reduce_1,
	parser_reduce_2,
	parser_reduce_3,
	parser_reduce_4,
};

static t_token_kind	_parse_shift(t_parser *pst, t_parser_state state,
	t_token_kind token)
{
	parser_stack_reserve(pst, 1);
	clear_parser_stack_item(++pst->now);
	pst->now->state = state;
	pst->now->kind = token;
	if (token == TK_WORD)
		swap_ptr(&pst->now->word, &pst->backup_word);
	return (TK_AGAIN);
}

static t_parser_state	_parse_reduce(t_parser *pst, t_parser_state state)
{
	const t_token_kind	token = (*g_grammer[-state])(pst);

	state = parser_state(pst->now[-1].state, token);
	pst->now->state = state;
	pst->now->kind = token;
	return (state);
}

static void	_parse_on_error(t_parser *pst, t_token_kind token)
{
	char *const	tok = get_token_str(token);

	if (pst->str && token == TK_EOF)
	{
		pst->error = PE_AGAIN;
		return ;
	}
	printf("syntax error near unexpected token `%s'\n", tok);
	pst->error = PE_SYNTAX_ERROR;
}

int	parse(t_parser *pst)
{
	t_parser_state	state;
	t_token_kind	token;

	state = 0;
	token = TK_AGAIN;
	pst->now->state = state;
	pst->now->kind = token;
	while (pst->error == PE_SUCCESS)
	{
		if (token == TK_AGAIN)
			token = read_token(pst);
		if (token == TK_ERROR)
			break ;
		state = parser_state(state, token);
		if (state == PARSER_ACCEPT)
			return (1);
		else if (state == PARSER_ERROR)
			_parse_on_error(pst, token);
		else if (state < 0)
			state = _parse_reduce(pst, state);
		else
			token = _parse_shift(pst, state, token);
	}
	return (0);
}
