/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 00:35:11 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAMMAR_H
# define GRAMMAR_H

# include "tokenizer.h"
# include "environment.h"
# include "redirections.h"
# include <stdbool.h>
# include <libft/libft.h>

/* ************************************************************************** */
/* GRAMMAR																	  */
/* ************************************************************************** */

typedef struct s_session	t_session;

typedef struct s_simple_command
{
	t_vector	argv;
	t_vector	redirs;
}	t_simple_command;

bool	parse_argument(t_vector *argv, t_tokenizer *tokenizer,
			enum e_parsing_error *error);

bool	alloc_simple_command(t_simple_command *cmd);
bool	parse_simple_command(t_simple_command *cmd, t_tokenizer *tokenizer,
			enum e_parsing_error *error);
bool	run_simple_command(t_simple_command *cmd, t_env *env,
			t_u8 *exit_status);
void	free_simple_command(t_simple_command cmd);

bool	run_raw_command(t_vector argv, t_env *env, t_backup_fds backup,
			t_u8 *exit_status);

bool	next_pipe(int *input, int pipe_fds[2], bool first, bool last);
bool	apply_pipe(int *input, int pipe_fds[2]);

bool	alloc_pipeline(t_vector *pipeline);
bool	parse_pipeline(t_vector *pipeline, t_tokenizer *tokenizer,
			enum e_parsing_error *error);
bool	run_pipeline(t_vector pipeline, t_session *session);
void	free_pipeline(t_vector pipeline);

typedef struct s_ast_root
{
	t_vector	pipes;
}	t_ast_root;

bool	parse_linebreak(t_tokenizer *tokenizer, const char *prompt,
			enum e_parsing_error *error);
bool	parse_newline_list(t_tokenizer *tokenizer, const char *prompt,
			enum e_parsing_error *error);

bool	alloc_ast(t_ast_root *ast);
bool	parse_ast(t_ast_root *ast, t_lines *lines, enum e_parsing_error *error);
bool	run_ast(t_ast_root ast, t_session *session);
void	free_ast(t_ast_root ast);

#endif