/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 03:50:21 by vchakhno         ###   ########.fr       */
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

t_read_input_status		parse_token(t_shell_input *input, t_token *token,
							const char *prompt, t_u8 *exit_status);
t_str					get_token_content(t_shell_input input, t_token token);
void					print_token(t_shell_input input, t_token token);

bool					check_ops(t_shell_input input, t_u32 *len);
bool					match_ops(t_shell_input *input, t_token *token);

typedef struct s_tokenizer
{
	t_vector		tokens;
	t_shell_input	*input;
}	t_tokenizer;

typedef enum e_parsing_status
{
	PARSING_SUCCEEDED,
	PARSING_CANCELED,
	PARSING_EXITED,
	PARSING_FAILED,
}	t_parsing_status;

bool					alloc_tokenizer(t_tokenizer *tokenizer,
							t_shell_input *input);
t_parsing_status		match_token(t_tokenizer *tokenizer, char *content,
							const char *prompt, t_u8 *exit_status);
t_parsing_status		match_word_token(t_tokenizer *tokenizer, t_str *content,
							const char *prompt, t_u8 *exit_status);
t_read_input_status		peek_token(t_tokenizer *tokenizer, t_token *token,
							const char *prompt, t_u8 *exit_status);
t_read_input_status		tokenize_line(t_tokenizer *tokenizer,
							const char *prompt, t_u8 *exit_status);
t_read_input_status		consume_token(t_tokenizer *tokenizer,
							const char *prompt, t_u8 *exit_status);
void					free_tokenizer(t_tokenizer tokenizer);

#endif