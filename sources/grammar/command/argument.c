/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/29 05:30:20 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_argument(
	t_vector *argv, t_tokenizer *tokenizer, enum e_syntax_error *error
) {
	t_token		token;
	t_string	arg;

	if (!peek_token(tokenizer, &token, "cmd> ", (enum e_prompt_error *)error))
		return (false);
	if (token.type != TOKEN_WORD)
	{
		*error = SYNTAX_ERROR_NO_MATCH;
		return (false);
	}
	consume_token(tokenizer, NULL, NULL);
	if (!ft_string_from_str(&arg, get_token_content(*tokenizer->lines, token)))
	{
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	if (!ft_vector_push(argv, &arg))
	{
		ft_string_free(arg);
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	return (true);
}