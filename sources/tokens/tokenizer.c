/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:48:18 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/26 02:59:47 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	alloc_tokenizer(t_tokenizer *tokenizer, t_lines *lines)
{
	if (!ft_vector_alloc(&tokenizer->tokens, sizeof(t_token), 30))
		return (false);
	tokenizer->lines = lines;
	return (true);
}

bool	match_token(
	t_tokenizer *tokenizer, char *content, const char *prompt,
	enum e_parsing_error *error
) {
	t_token	token;

	if (!peek_token(tokenizer, &token, prompt, (enum e_prompt_error *)error))
		return (false);
	if (!ft_str_equal_c_str(
			get_token_content(*tokenizer->lines, token), content))
	{
		*error = PARSING_ERROR_SYNTAX;
		return (false);
	}
	ft_vector_remove(&tokenizer->tokens, 0, NULL);
	return (true);
}

bool	match_word_token(
	t_tokenizer *tokenizer, t_str *content, const char *prompt,
	enum e_parsing_error *error
) {
	t_token	token;

	if (!peek_token(tokenizer, &token, prompt, (enum e_prompt_error *)error))
		return (false);
	if (token.type != TOKEN_WORD)
	{
		*error = PARSING_ERROR_SYNTAX;
		return (false);
	}
	ft_vector_remove(&tokenizer->tokens, 0, NULL);
	*content = get_token_content(*tokenizer->lines, token);
	return (true);
}

bool	peek_token(
	t_tokenizer *tokenizer, t_token *token, const char *prompt,
	enum e_prompt_error *error
) {
	if (tokenizer->tokens.size == 0 && !tokenize_line(tokenizer, prompt, error))
		return (false);
	*token = ((t_token *)tokenizer->tokens.elems)[0];
	return (true);
}

bool	consume_token(
	t_tokenizer *tokenizer, const char *prompt,
	enum e_prompt_error *error
) {
	if (tokenizer->tokens.size == 0 && !tokenize_line(tokenizer, prompt, error))
		return (false);
	ft_vector_remove(&tokenizer->tokens, 0, NULL);
	return (true);
}

bool	tokenize_line(
	t_tokenizer *tokenizer, const char *prompt, enum e_prompt_error *error
) {
	t_token	token;

	while (parse_token(tokenizer->lines, &token, prompt, error))
	{
		if (!ft_vector_push(&tokenizer->tokens, &token))
		{
			*error = PROMPT_ERROR_CANCEL;
			return (false);
		}
		if (ft_str_equal_c_str(
				get_token_content(*tokenizer->lines, token), "\n"))
			return (true);
	}
	return (false);
}

void	free_tokenizer(t_tokenizer tokenizer)
{
	ft_vector_free(tokenizer.tokens);
}
