/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:48:18 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 14:11:49 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	skip_blanks(t_shell_input *input)
{
	while (input->cursor < input->text.len
		&& (input->text.c_str[input->cursor] == ' '
			|| input->text.c_str[input->cursor] == '\t'))
		input->cursor++;
}

// false -> any error (CTRL+C, CTRL+D, malloc)

t_read_input_status	skip_quotes(t_shell_input *input, t_u8 *exit_status)
{
	t_read_input_status	status;
	char				quote;
	const char			*prompt;

	quote = input->text.c_str[input->cursor];
	if (quote == '\'')
		prompt = "quote> ";
	else
		prompt = "dquote> ";
	input->cursor++;
	while (input->text.c_str[input->cursor] != quote)
	{
		if (input->cursor == input->text.len)
		{
			status = append_lines(input, prompt, exit_status);
			if (status != READING_SUCCEEDED)
				return (status);
		}
		else
			input->cursor++;
	}
	return (READING_SUCCEEDED);
}

// false -> unterminated token

bool	skip_word(t_shell_input *input)
{
	while (input->cursor < input->text.len
		&& !check_ops(*input, NULL)
		&& input->text.c_str[input->cursor] != ' '
		&& input->text.c_str[input->cursor] != '\t')
	{
		if (input->text.c_str[input->cursor] == '\"'
			|| input->text.c_str[input->cursor] == '\'')
			return (false);
		input->cursor++;
	}
	return (true);
}

// false -> any error (CTRL+C, CTRL+D, malloc)

t_read_input_status	parse_token(
	t_shell_input *input, t_token *token, const char *prompt, t_u8 *exit_status
) {
	t_read_input_status	status;

	if (input->cursor == input->text.len)
	{
		status = append_lines(input, prompt, exit_status);
		if (status != READING_SUCCEEDED)
			return (status);
	}
	skip_blanks(input);
	token->start = input->cursor;
	if (match_ops(input, token))
		return (READING_SUCCEEDED);
	token->type = TOKEN_WORD;
	while (!skip_word(input))
	{
		status = skip_quotes(input, exit_status);
		if (status != READING_SUCCEEDED)
			return (status);
		input->cursor++;
	}
	token->len = input->cursor - token->start;
	return (READING_SUCCEEDED);
}

t_read_input_status	tokenize_line(
	t_tokenizer *tokenizer, const char *prompt, t_u8 *exit_status
) {
	t_read_input_status	status;
	t_token				token;

	status = parse_token(tokenizer->input, &token, prompt, exit_status);
	while (status == READING_SUCCEEDED)
	{
		if (!ft_vector_push(&tokenizer->tokens, &token))
			return (READING_CANCELED);
		if (ft_str_equal_c_str(
				get_token_content(*tokenizer->input, token), "\n"))
			return (READING_SUCCEEDED);
		status = parse_token(tokenizer->input, &token, prompt, exit_status);
	}
	return (status);
}
