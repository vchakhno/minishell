/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 07:06:32 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

t_parsing_status	parse_argument(t_vector *argv, t_tokenizer *tokenizer)
{
	t_parsing_status	status;
	t_token				token;
	t_string			arg;

	status = (t_parsing_status) peek_token(tokenizer, &token, "cmd> ");
	if (status != PARSING_SUCCEEDED)
		return (status);
	if (token.type != TOKEN_WORD)
		return (PARSING_FAILED);
	consume_token(tokenizer, NULL);
	if (!ft_string_from_str(&arg, get_token_content(*tokenizer->input, token)))
		return (PARSING_CANCELED);
	if (!ft_vector_push(argv, &arg))
	{
		ft_string_free(arg);
		return (PARSING_CANCELED);
	}
	return (PARSING_SUCCEEDED);
}
