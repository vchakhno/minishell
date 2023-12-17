/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:48:18 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/17 18:47:50 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_ops(t_program program, t_str *op)
{
	char *const	ops[] = {
		"<<", "<", ">>", ">", "&&", "||", "|", "(", ")", "\n"
	};
	t_str		program_str;
	t_u32		i;

	program_str.c_str = program.c_str + program.cursor;
	program_str.len = program.len - program.cursor;
	i = 0;
	while (i < (int) sizeof ops / sizeof * ops)
	{
		if (ft_str_starts_with_c_str(program_str, ops[i]))
		{
			if (op)
				*op = ft_str(ops[i]);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	match_ops(t_program *program, t_token *token)
{
	if (check_ops(*program, &token->content))
	{
		token->type = TOKEN_OP;
		program->cursor += token->content.len;
		return (true);
	}
	return (false);
}

void	skip_blanks(t_program *program)
{
	while (program->cursor < program->len
		&& program->c_str[program->cursor] == ' ')
		program->cursor++;
}

// bool -> any error (CTRL+C, CTRL+D, malloc)

bool	parse_quotes(
	t_program *program, t_token *token, const char *prompt,
	enum e_program_error *error
) {
	char	quote;

	quote = program->c_str[program->cursor];
	token->content.len++;
	program->cursor++;
	while (program->cursor < program->len)
	{
		if (program->c_str[program->cursor] == quote)
			return (true);
		token->content.len++;
		program->cursor++;
	}
	while (get_program_lines(program, prompt, error))
	{
		while (program->cursor < program->len)
		{
			if (program->c_str[program->cursor] == quote)
				return (true);
			token->content.len++;
			program->cursor++;
		}
	}
	return (false);
}

// bool -> unterminated token

bool	parse_word(t_program *program, t_token *token)
{
	while (program->cursor < program->len
		&& !check_ops(*program, NULL)
		&& program->c_str[program->cursor] != ' ')
	{
		if (program->c_str[program->cursor] == '\"'
			|| program->c_str[program->cursor] == '\'')
			return (false);
		token->content.len++;
		program->cursor++;
	}
	return (true);
}

// bool -> any error (CTRL+C, CTRL+D, malloc)

bool	parse_token(
	t_program *program, t_token *token, const char *prompt,
	enum e_program_error *error
) {
	skip_blanks(program);
	while (program->cursor == program->len)
	{
		if (!get_program_lines(program, prompt, error))
			return (false);
		skip_blanks(program);
	}
	if (match_ops(program, token))
		return (true);
	token->type = TOKEN_WORD;
	token->content.c_str = program->c_str + program->cursor;
	token->content.len = 0;
	while (!parse_word(program, token))
	{
		if (!parse_quotes(program, token, "quote> ", error))
			return (false);
		token->content.len++;
		program->cursor++;
	}
	return (true);
}

void	print_token(t_token token)
{
	ft_println("({c_str}, \"{str}\")",
		(char *[]){"OP", "WORD"}[token.type], token.content);
}
