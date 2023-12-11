/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:48:18 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/11 12:48:17 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pseudo tokenization according to whitespace

bool	parse_token(t_token *token, t_program *program)
{
	t_u32	start;
	t_u32	len;

	start = program->cmd_cursor;
	while (start < program->text.len
		&& ft_char_is_blank(program->text.c_str[start]))
		start++;
	if (start == program->text.len
		&& !get_program(program, PROMPT))
		return (false);
	while (start < program->text.len
		&& ft_char_is_blank(program->text.c_str[start]))
		start++;
	len = 0;
	while (start + len < program->text.len
		&& !ft_char_is_blank(program->text.c_str[start + len]))
		len++;
	token->content.c_str = &program->text.c_str[start];
	token->content.len = len;
	token->type = TOKEN_IDENT;
	program->cmd_cursor = start + len;
	return (true);
}

bool	refill_tokens(t_vector *tokens, t_program *program)
{
	t_token	token;

	return (
		parse_token(&token, program)
		&& ft_vector_push(tokens, &token)
	);
}

bool	peek_token(t_vector *tokens, t_token *token, t_program *program)
{
	if (tokens->size == 0 && !refill_tokens(tokens, program))
		return (false);
	*token = ((t_token *)tokens->elems)[0];
	return (true);
}

bool	match_token(
	t_vector *tokens, char *str, t_program *program, bool *matches
) {
	if (tokens->size == 0 && !refill_tokens(tokens, program))
		return (false);
	if (ft_str_equal_c_str(((t_token *)tokens->elems)[0].content, str))
	{
		*matches = true;
		ft_vector_remove(tokens, 0, NULL);
	}
	else
	{
		*matches = false;
	}
	return (true);
}
