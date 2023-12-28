/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:48:18 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/28 18:49:57 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_ops(t_lines lines, t_u32 *len)
{
	char *const	ops[] = {
		"<<", "<", ">>", ">", "&&", "||", "|", "(", ")", "\n"
	};
	t_str		lines_str;
	t_u32		i;

	lines_str.c_str = lines.text.c_str + lines.cursor;
	lines_str.len = lines.text.len - lines.cursor;
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

bool	match_ops(t_lines *lines, t_token *token)
{
	if (check_ops(*lines, &token->len))
	{
		token->type = TOKEN_OP;
		lines->cursor += token->len;
		return (true);
	}
	return (false);
}

void	skip_blanks(t_lines *lines)
{
	while (lines->cursor < lines->text.len
		&& lines->text.c_str[lines->cursor] == ' ')
		lines->cursor++;
}

// false -> any error (CTRL+C, CTRL+D, malloc)

bool	skip_quotes(t_lines *lines, enum e_prompt_error *error)
{
	char		quote;
	const char	*prompt;

	quote = lines->text.c_str[lines->cursor];
	if (quote == '\'')
		prompt = "quote> ";
	else
		prompt = "dquote> ";
	lines->cursor++;
	while (lines->text.c_str[lines->cursor] != quote)
	{
		if (lines->cursor == lines->text.len
			&& !append_lines(lines, prompt, error))
			return (false);
		else
			lines->cursor++;
	}
	return (true);
}

// false -> unterminated token

bool	skip_word(t_lines *lines)
{
	while (lines->cursor < lines->text.len
		&& !check_ops(*lines, NULL)
		&& lines->text.c_str[lines->cursor] != ' ')
	{
		if (lines->text.c_str[lines->cursor] == '\"'
			|| lines->text.c_str[lines->cursor] == '\'')
			return (false);
		lines->cursor++;
	}
	return (true);
}

// false -> any error (CTRL+C, CTRL+D, malloc)

bool	parse_token(
	t_lines *lines, t_token *token, const char *prompt,
	enum e_prompt_error *error
) {

	if (lines->cursor == lines->text.len && !append_lines(lines, prompt, error))
		return (false);
	skip_blanks(lines);
	token->start = lines->cursor;
	if (match_ops(lines, token))
		return (true);
	token->type = TOKEN_WORD;
	while (!skip_word(lines))
	{
		if (!skip_quotes(lines, error))
			return (false);
		lines->cursor++;
	}
	token->len = lines->cursor - token->start;
	return (true);
}

t_str	get_token_content(t_lines lines, t_token token)
{
	return (ft_str_get_slice(lines.text.str, token.start, token.len));
}

void	print_token(t_lines lines, t_token token)
{
	ft_println("({c_str}, \"{str}\")",
		(char *[]){"OP", "WORD"}[token.type], get_token_content(lines, token));
}
