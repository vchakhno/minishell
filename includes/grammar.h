/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 10:50:16 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAMMAR_H
# define GRAMMAR_H

# include "tokenizer.h"
# include "runtime_context.h"
# include "redirections.h"
# include <stdbool.h>
# include <libft/libft.h>

typedef struct s_simple_command
{
	t_vector	argv;
	t_vector	redirs;
}	t_simple_command;

t_parsing_status	parse_argument(t_vector *argv, t_tokenizer *tokenizer);

bool				alloc_simple_command(t_simple_command *cmd);
t_parsing_status	parse_simple_command(t_simple_command *cmd,
						t_tokenizer *tokenizer);
bool				run_simple_command(t_simple_command *cmd,
						t_runtime_context *context);
void				free_simple_command(t_simple_command cmd);

bool				run_raw_command(t_vector argv, t_runtime_context *context,
						t_backup_fds backup);

bool				next_pipe(int *input, int pipe_fds[2],
						bool first, bool last);
bool				apply_pipe(int *input, int pipe_fds[2]);

bool				alloc_pipeline(t_vector *pipeline);
t_parsing_status	parse_pipeline(t_vector *pipeline, t_tokenizer *tokenizer);
bool				run_pipeline(t_vector pipeline, t_runtime_context *context);
void				free_pipeline(t_vector pipeline);

typedef enum e_and_or_elem_kind {
	AND_ELEM,
	OR_ELEM,
}	t_and_or_elem_kind;

typedef struct s_and_or_elem
{
	t_and_or_elem_kind	kind;
	t_vector			pipeline;
}	t_and_or_elem;

bool				alloc_and_or(t_vector *and_or);
t_parsing_status	parse_and_or(t_vector *and_or, t_tokenizer *tokenizer);
bool				run_and_or(t_vector and_or, t_runtime_context *context);
void				free_and_or(t_vector and_or);

typedef struct s_ast_root
{
	t_vector	and_or;
}	t_ast_root;

t_parsing_status	parse_linebreak(t_tokenizer *tokenizer, const char *prompt);
t_parsing_status	parse_newline_list(t_tokenizer *tokenizer,
						const char *prompt);

bool				alloc_ast(t_ast_root *ast);
t_parsing_status	parse_ast(t_ast_root *ast, t_shell_input *input);
bool				run_ast(t_ast_root ast, t_runtime_context *context);
void				free_ast(t_ast_root ast);

#endif