/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 00:31:10 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

bool	parse_argument(
	t_vector *argv, t_tokenizer *tokenizer, enum e_parsing_error *error
) {
	t_token		token;
	t_string	arg;

	if (!peek_token(tokenizer, &token, "cmd> ", (enum e_prompt_error *)error))
		return (false);
	if (token.type != TOKEN_WORD)
	{
		*error = PARSING_ERROR_SYNTAX;
		return (false);
	}
	consume_token(tokenizer, NULL, NULL);
	if (!ft_string_from_str(&arg, get_token_content(*tokenizer->lines, token)))
	{
		*error = PARSING_ERROR_CANCEL;
		return (false);
	}
	if (!ft_vector_push(argv, &arg))
	{
		ft_string_free(arg);
		*error = PARSING_ERROR_CANCEL;
		return (false);
	}
	return (true);
}
