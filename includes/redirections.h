/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 01:13:40 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "tokenizer.h"
# include "runtime_context.h"
# include <stdbool.h>
# include <libft/libft.h>

/* ************************************************************************** */
/* REDIRECTIONS																  */
/* ************************************************************************** */

typedef struct s_output_redir
{
	t_string	filename;
}	t_output_redir;

bool	parse_output_redir(t_output_redir *redir, t_tokenizer *tokenizer,
			enum e_parsing_error *error);
bool	run_output_redir(t_output_redir *redir, t_runtime_context context);
void	free_output_redir(t_output_redir redir);

typedef struct s_append_redir
{
	t_string	filename;
}	t_append_redir;

bool	parse_append_redir(t_append_redir *redir, t_tokenizer *tokenizer,
			enum e_parsing_error *error);
bool	run_append_redir(t_append_redir *redir, t_runtime_context context);
void	free_append_redir(t_append_redir redir);

typedef struct s_input_redir
{
	t_string	filename;
}	t_input_redir;

bool	parse_input_redir(t_input_redir *redir, t_tokenizer *tokenizer,
			enum e_parsing_error *error);
bool	run_input_redir(t_input_redir *redir, t_runtime_context context);
void	free_input_redir(t_input_redir redir);

typedef struct s_heredoc
{
	t_string	delimiter;
	t_string	body;
	pid_t		pid;
}	t_heredoc;

bool	parse_heredoc(t_heredoc *heredoc, t_tokenizer *tokenizer,
			enum e_parsing_error *error);
bool	run_heredoc(t_heredoc *heredoc, bool *recovers);
void	cleanup_heredoc(t_heredoc heredoc);
void	free_heredoc(t_heredoc heredoc);

enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_HEREDOC,
	REDIR_APPEND,
};

typedef struct s_redirection
{
	enum e_redir_type	type;
	union {
		t_output_redir	output;
		t_input_redir	input;
		t_append_redir	append;
		t_heredoc		heredoc;
	};
}	t_redirection;

bool	run_redirection(t_redirection *redir, bool *recovers,
			t_runtime_context context);
bool	parse_redirection(t_redirection *redir, t_tokenizer *tokenizer,
			enum e_parsing_error *error);
void	cleanup_redirection(t_redirection redir);
void	free_redirection(t_redirection redir);

typedef struct s_backup_fds
{
	t_i32	stdin;
	t_i32	stdout;
}	t_backup_fds;

bool	save_backup_fds(t_backup_fds *backup);
bool	restore_backup_fds(t_backup_fds backup);
void	discard_backup_fds(t_backup_fds backup);

bool	parse_redirections(t_vector *redirs, t_tokenizer *tokenizer,
			enum e_parsing_error *error);
bool	run_redirections(t_vector redirs, t_backup_fds *backup,
			bool *recovers, t_runtime_context context);
void	cleanup_redirections(t_vector redirs, t_backup_fds backup, t_u32 size);

#endif