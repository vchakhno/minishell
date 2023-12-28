/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:48:18 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/28 10:02:13 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_ops(t_lines lines, t_str *op)
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
			if (op)
				*op = ft_str(ops[i]);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	match_ops(t_lines *lines, t_token *token)
{
	if (check_ops(*lines, &token->content))
	{
		token->type = TOKEN_OP;
		lines->cursor += token->content.len;
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

// bool -> any error (CTRL+C, CTRL+D, malloc)

bool	parse_quotes(
	t_lines *lines, t_token *token, const char *prompt,
	enum e_prompt_error *error
) {
	char	quote;

	quote = lines->text.c_str[lines->cursor];
	token->content.len++;
	lines->cursor++;
	while (lines->cursor < lines->text.len)
	{
		if (lines->text.c_str[lines->cursor] == quote)
			return (true);
		token->content.len++;
		lines->cursor++;
	}
	while (append_lines(lines, prompt, error))
	{
		while (lines->cursor < lines->text.len)
		{
			if (lines->text.c_str[lines->cursor] == quote)
				return (true);
			token->content.len++;
			lines->cursor++;
		}
	}
	return (false);
}

// bool -> unterminated token

bool	parse_word(t_lines *lines, t_token *token)
{
	while (lines->cursor < lines->text.len
		&& !check_ops(*lines, NULL)
		&& lines->text.c_str[lines->cursor] != ' ')
	{
		if (lines->text.c_str[lines->cursor] == '\"'
			|| lines->text.c_str[lines->cursor] == '\'')
			return (false);
		token->content.len++;
		lines->cursor++;
	}
	return (true);
}

// bool -> any error (CTRL+C, CTRL+D, malloc)

bool	parse_token(
	t_lines *lines, t_token *token, const char *prompt,
	enum e_prompt_error *error
) {
	skip_blanks(lines);
	while (lines->cursor == lines->text.len)
	{
		if (!append_lines(lines, prompt, error))
			return (false);
		skip_blanks(lines);
	}
	if (match_ops(lines, token))
		return (true);
	token->type = TOKEN_WORD;
	token->content.c_str = lines->text.c_str + lines->cursor;
	token->content.len = 0;
	while (!parse_word(lines, token))
	{
		if (!parse_quotes(lines, token, "quote> ", error))
			return (false);
		token->content.len++;
		lines->cursor++;
	}
	return (true);
}

void	print_token(t_token token)
{
	ft_println("({c_str}, \"{str}\")",
		(char *[]){"OP", "WORD"}[token.type], token.content);
}
