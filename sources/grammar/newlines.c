/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newlines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:00:31 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/26 02:59:05 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Can fail if readline fails
bool	parse_linebreak(
	t_tokenizer *tokenizer, const char *prompt, enum e_parsing_error *error
) {
	while (match_token(tokenizer, "\n", prompt, error))
		;
	return (*error == PARSING_ERROR_SYNTAX);
}

bool	parse_newline_list(
	t_tokenizer *tokenizer, const char *prompt, enum e_parsing_error *error
) {
	if (match_token(tokenizer, "\n", prompt, error))
		return (false);
	while (match_token(tokenizer, "\n", prompt, error))
		;
	return (*error == PARSING_ERROR_SYNTAX);
}