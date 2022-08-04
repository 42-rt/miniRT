/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:36:15 by jkong             #+#    #+#             */
/*   Updated: 2022/08/04 14:02:21 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>

# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>

typedef struct s_entry
{
	char			*value;
	struct s_entry	*child;
	struct s_entry	*next;
}	t_entry;

enum	e_char_flag_index
{
	CF_META,
	CF_BREAK,
	CF_BLANK,
};

typedef enum e_char_flag
{
	CFV_WORD = 0,
	CFV_META = 1 << CF_META,
	CFV_BREAK = 1 << CF_BREAK,
	CFV_BLANK = 1 << CF_BLANK,
}	t_char_flags;

typedef enum e_token_kind
{
	TK_AGAIN = 0,
	TK_PAREN_L = '{',
	TK_PAREN_R = '}',
	TK_EOF = 256,
	TK_ERROR,
	TK_UNDEFINED,
	TK_WORD,
	TK_NT_ACCEPT = 512,
	TK_NT_ELEMENT,
	TK_NT_LIST,
}	t_token_kind;

# define PARSER_ACCEPT -1000
# define PARSER_ERROR -1001

typedef int				t_parser_state;

typedef enum e_parser_error
{
	PE_SUCCESS,
	PE_AGAIN,
	PE_SYNTAX_ERROR,
}	t_parser_error;

typedef struct s_parser_stack
{
	t_parser_state	state;
	t_token_kind	kind;
	char			*word;
	t_entry			*entry;
}	t_parser_stack;

typedef struct s_parser
{
	char					*begin;
	char					*str;
	char					*backup_word;
	t_parser_error			error;
	size_t					stack_capacity;
	t_parser_stack			*stack_base;
	t_parser_stack			*now;
}	t_parser;

typedef struct s_state_info
{
	t_token_kind			token;
	t_parser_state			state;
}	t_state_info;

typedef t_token_kind	t_parse_func(t_parser *);

t_char_flags	char_flags(int c);
size_t			next_syntax(char *s, t_char_flags flag);
t_token_kind	read_token(t_parser *pst);
int				parse(t_parser *pst);
t_parser_state	parser_state(t_parser_state state, t_token_kind token);

t_token_kind	parser_reduce_0(t_parser *pst);
t_token_kind	parser_reduce_1(t_parser *pst);
t_token_kind	parser_reduce_2(t_parser *pst);
t_token_kind	parser_reduce_3(t_parser *pst);
t_token_kind	parser_reduce_4(t_parser *pst);

t_entry			*make_entry(void);
void			dispose_entry(t_entry *item);

char			*get_token_str(t_token_kind token);
void			swap_ptr(void *a, void *b);
void			clear_parser_stack_item(t_parser_stack *item);
void			parser_stack_reserve(t_parser *pst, size_t n);
void			parser_stack_remove_all(t_parser *pst);

#endif
