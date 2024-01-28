/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newlines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:00:31 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 09:38:38 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

// Can fail if readline fails
// Zero or more lines
t_parsing_status	parse_linebreak(t_tokenizer *tokenizer, const char *prompt)
{
	t_parsing_status	status;

	status = match_token(tokenizer, "\n", prompt);
	if (status == PARSING_CANCELED || status == PARSING_EXITED)
		return (status);
	while (status != PARSING_FAILED)
	{
		status = match_token(tokenizer, "\n", prompt);
		if (status == PARSING_CANCELED || status == PARSING_EXITED)
			return (status);
	}
	return (PARSING_SUCCEEDED);
}

// One or more lines
t_parsing_status	parse_newline_list(
	t_tokenizer *tokenizer, const char *prompt
) {
	t_parsing_status	status;

	status = match_token(tokenizer, "\n", prompt);
	if (status != PARSING_SUCCEEDED)
		return (status);
	while (status != PARSING_FAILED)
	{
		status = match_token(tokenizer, "\n", prompt);
		if (status == PARSING_CANCELED || status == PARSING_EXITED)
			return (status);
	}
	return (PARSING_SUCCEEDED);
}
