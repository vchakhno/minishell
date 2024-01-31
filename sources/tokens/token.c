/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:48:18 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 00:46:05 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool	check_ops(t_shell_input input, t_u32 *len)
{
	char *const	ops[] = {
		"<<", "<", ">>", ">", "&&", "||", "|", "(", ")", "\n"
	};
	t_str		lines_str;
	t_u32		i;

	lines_str.c_str = input.text.c_str + input.cursor;
	lines_str.len = input.text.len - input.cursor;
	i = 0;
	while (i < (int) sizeof ops / sizeof * ops)
	{
		if (ft_str_starts_with_c_str(lines_str, ops[i]))
		{
			if (len)
				*len = ft_c_str_len(ops[i]);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	match_ops(t_shell_input *input, t_token *token)
{
	if (check_ops(*input, &token->len))
	{
		token->type = TOKEN_OP;
		input->cursor += token->len;
		return (true);
	}
	return (false);
}

void	skip_blanks(t_shell_input *input)
{
	while (input->cursor < input->text.len
		&& input->text.c_str[input->cursor] == ' ')
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
		&& input->text.c_str[input->cursor] != ' ')
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

t_str	get_token_content(t_shell_input input, t_token token)
{
	return (ft_str_get_slice(input.text.str, token.start, token.len));
}

void	print_token(t_shell_input input, t_token token)
{
	ft_println("({c_str}, \"{str}\")",
		(char *[]){"OP", "WORD"}[token.type], get_token_content(input, token));
}
