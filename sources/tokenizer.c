/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:48:18 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/17 21:25:12 by vchakhno         ###   ########.fr       */
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
	enum e_syntax_error *error
) {
	t_token	token;

	if (!peek_token(tokenizer, &token, prompt, (enum e_prompt_error *)error))
		return (false);
	if (ft_str_equal_c_str(token.content, content))
	{
		ft_vector_remove(&tokenizer->tokens, 0, NULL);
		return (true);
	}
	*error = SYNTAX_ERROR_NO_MATCH;
	return (false);
}

bool	peek_token(
	t_tokenizer *tokenizer, t_token *token, const char *prompt,
	enum e_prompt_error *error
) {
	if (tokenizer->tokens.size > 0)
	{
		*token = ((t_token *)tokenizer->tokens.elems)[0];
		return (true);
	}
	if (!parse_token(tokenizer->lines, token, prompt, error))
		return (false);
	if (!ft_vector_push(&tokenizer->tokens, token))
	{
		*error = PROMPT_ERROR_MALLOC;
		return (false);
	}
	return (true);
}

bool	consume_token(
	t_tokenizer *tokenizer, const char *prompt,
	enum e_prompt_error *error
) {
	if (tokenizer->tokens.size > 0)
	{
		ft_vector_remove(&tokenizer->tokens, 0, NULL);
		return (true);
	}
	return (parse_token(tokenizer->lines, &(t_token){0}, prompt, error));
}

void	free_tokenizer(t_tokenizer tokenizer)
{
	ft_vector_free(tokenizer.tokens);
}
