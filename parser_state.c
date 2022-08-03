/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/08/03 16:06:53 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static const t_state_info			g_parser_state_0[] = {
	(t_state_info){TK_WORD, 3},
	(t_state_info){TK_NT_ELEMENT, 2},
	(t_state_info){TK_NT_LIST, 1},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_1[] = {
	(t_state_info){TK_WORD, 3},
	(t_state_info){TK_EOF, PARSER_ACCEPT},
	(t_state_info){TK_NT_ELEMENT, 4},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_2[] = {
	(t_state_info){TK_WORD, -3},
	(t_state_info){TK_PAREN_R, -3},
	(t_state_info){TK_EOF, -3},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_3[] = {
	(t_state_info){TK_WORD, -1},
	(t_state_info){TK_PAREN_L, 5},
	(t_state_info){TK_PAREN_R, -1},
	(t_state_info){TK_EOF, -1},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_4[] = {
	(t_state_info){TK_WORD, -4},
	(t_state_info){TK_PAREN_R, -4},
	(t_state_info){TK_EOF, -4},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_5[] = {
	(t_state_info){TK_WORD, 3},
	(t_state_info){TK_NT_ELEMENT, 2},
	(t_state_info){TK_NT_LIST, 6},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_6[] = {
	(t_state_info){TK_WORD, 3},
	(t_state_info){TK_PAREN_R, 7},
	(t_state_info){TK_NT_ELEMENT, 4},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_7[] = {
	(t_state_info){TK_WORD, -2},
	(t_state_info){TK_PAREN_R, -2},
	(t_state_info){TK_EOF, -2},
	(t_state_info){TK_ERROR, PARSER_ERROR}
};

static const t_state_info *const	g_parser_state_table[] = {
	g_parser_state_0,
	g_parser_state_1,
	g_parser_state_2,
	g_parser_state_3,
	g_parser_state_4,
	g_parser_state_5,
	g_parser_state_6,
	g_parser_state_7,
};

t_parser_state	parser_state(t_parser_state state, t_token_kind token)
{
	const t_state_info	*info = g_parser_state_table[state];
	size_t				i;

	i = 0;
	while (info[i].token != TK_ERROR)
	{
		if (info[i].token == token)
			return (info[i].state);
		i++;
	}
	return (PARSER_ERROR);
}
