/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 00:55:42 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "shell_input.h"
# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>
# include <libft/libft.h>
# include <sys/types.h>

/* ************************************************************************** */
/* TOKENS																	  */
/* ************************************************************************** */

enum	e_token_type
{
	TOKEN_OP,
	TOKEN_WORD,
};

typedef struct s_token
{
	enum e_token_type	type;
	t_u32				start;
	t_u32				len;
}	t_token;

bool	parse_token(t_shell_input *input, t_token *token, const char *prompt,
			enum e_prompt_error *error);
t_str	get_token_content(t_shell_input input, t_token token);
void	print_token(t_shell_input input, t_token token);

/* ************************************************************************** */
/* TOKENIZER																  */
/* ************************************************************************** */

typedef struct s_tokenizer
{
	t_vector		tokens;
	t_shell_input	*input;
}	t_tokenizer;

enum	e_parsing_error
{
	PARSING_ERROR_CANCEL,
	PARSING_ERROR_EXIT,
	PARSING_ERROR_SYNTAX,
};

bool	alloc_tokenizer(t_tokenizer *tokenizer, t_shell_input *input);
bool	match_token(t_tokenizer *tokenizer, char *content, const char *prompt,
			enum e_parsing_error *error);
bool	match_word_token(t_tokenizer *tokenizer, t_str *content,
			const char *prompt, enum e_parsing_error *error);
bool	peek_token(t_tokenizer *tokenizer, t_token *token, const char *prompt,
			enum e_prompt_error *error);
bool	tokenize_line(t_tokenizer *tokenizer, const char *prompt,
			enum e_prompt_error *error);
bool	consume_token(t_tokenizer *tokenizer, const char *prompt,
			enum e_prompt_error *error);
void	free_tokenizer(t_tokenizer tokenizer);

#endif