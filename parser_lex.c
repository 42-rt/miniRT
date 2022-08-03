/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:18:56 by jkong             #+#    #+#             */
/*   Updated: 2022/08/03 22:05:11 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "util_flag.h"
#include "safe_mem.h"
#include "libft.h"

static t_token_kind	_read_token_word(t_parser *pst)
{
	size_t		len;
	char		*word;

	len = next_syntax(pst->str, CFV_BREAK);
	word = malloc_safe(len + 1);
	ft_memcpy(word, pst->str, len);
	word[len] = '\0';
	pst->str += len;
	free(pst->backup_word);
	pst->backup_word = word;
	return (TK_WORD);
}

static t_token_kind	_read_token_meta(t_parser *pst)
{
	t_token_kind	tok;

	tok = *pst->str++;
	return (tok);
}

t_token_kind	read_token(t_parser *pst)
{
	t_token_kind	result;

	pst->error = PE_SUCCESS;
	if (!pst->str)
		return (TK_EOF);
	result = TK_UNDEFINED;
	while (has_flag(char_flags(*pst->str), CF_BLANK))
		pst->str++;
	if (result == TK_UNDEFINED && *pst->str == '\0')
		result = TK_EOF;
	if (result == TK_UNDEFINED && has_flag(char_flags(*pst->str), CF_META))
		result = _read_token_meta(pst);
	if (result == TK_UNDEFINED)
		result = _read_token_word(pst);
	if (pst->error != PE_SUCCESS)
	{
		printf("unknown token\n");
		result = TK_ERROR;
	}
	return (result);
}
