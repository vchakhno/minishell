/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:48:18 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 01:44:16 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_parsing_status	match_token(
	t_tokenizer *tokenizer, char *content, const char *prompt, t_u8 *exit_status
) {
	t_read_input_status	status;
	t_token				token;

	status = peek_token(tokenizer, &token, prompt, exit_status);
	if (status != READING_SUCCEEDED)
		return ((t_parsing_status) status);
	if (!ft_str_equal_c_str(
			get_token_content(*tokenizer->input, token), content))
		return (PARSING_FAILED);
	ft_vector_remove(&tokenizer->tokens, 0, NULL);
	return (PARSING_SUCCEEDED);
}

t_parsing_status	match_word_token(
	t_tokenizer *tokenizer, t_str *content, const char *prompt,
	t_u8 *exit_status
) {
	t_read_input_status	status;
	t_token				token;

	status = peek_token(tokenizer, &token, prompt, exit_status);
	if (status != READING_SUCCEEDED)
		return ((t_parsing_status) status);
	if (token.type != TOKEN_WORD)
		return (PARSING_FAILED);
	ft_vector_remove(&tokenizer->tokens, 0, NULL);
	*content = get_token_content(*tokenizer->input, token);
	return (PARSING_SUCCEEDED);
}

t_read_input_status	peek_token(
	t_tokenizer *tokenizer, t_token *token, const char *prompt,
	t_u8 *exit_status
) {
	t_read_input_status	status;

	if (tokenizer->tokens.size == 0)
	{
		status = tokenize_line(tokenizer, prompt, exit_status);
		if (status != READING_SUCCEEDED)
			return (status);
	}
	*token = ((t_token *)tokenizer->tokens.elems)[0];
	return (READING_SUCCEEDED);
}

t_read_input_status	consume_token(
	t_tokenizer *tokenizer, const char *prompt, t_u8 *exit_status
) {
	t_read_input_status	status;

	if (tokenizer->tokens.size == 0)
	{
		status = tokenize_line(tokenizer, prompt, exit_status);
		if (status != READING_SUCCEEDED)
			return (status);
	}
	ft_vector_remove(&tokenizer->tokens, 0, NULL);
	return (READING_SUCCEEDED);
}
