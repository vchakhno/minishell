/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newlines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:00:31 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 00:47:25 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

// Can fail if readline fails
// Zero or more lines
t_parsing_status	parse_linebreak(
	t_tokenizer *tokenizer, const char *prompt, t_u8 *exit_status
) {
	t_parsing_status	status;

	status = match_token(tokenizer, "\n", prompt, exit_status);
	if (status == PARSING_CANCELED || status == PARSING_EXITED)
		return (status);
	while (status != PARSING_FAILED)
	{
		status = match_token(tokenizer, "\n", prompt, exit_status);
		if (status == PARSING_CANCELED || status == PARSING_EXITED)
			return (status);
	}
	return (PARSING_SUCCEEDED);
}

// One or more lines
t_parsing_status	parse_newline_list(
	t_tokenizer *tokenizer, const char *prompt, t_u8 *exit_status
) {
	t_parsing_status	status;

	status = match_token(tokenizer, "\n", prompt, exit_status);
	if (status != PARSING_SUCCEEDED)
		return (status);
	while (status != PARSING_FAILED)
	{
		status = match_token(tokenizer, "\n", prompt, exit_status);
		if (status == PARSING_CANCELED || status == PARSING_EXITED)
			return (status);
	}
	return (PARSING_SUCCEEDED);
}
