/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/22 21:57:16 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>
# include <libft/libft.h>
# include <sys/types.h>

/* ************************************************************************** */
/* PROMPTS																	  */
/* ************************************************************************** */

# define MAIN_PROMPT "\1\e[38;2;255;63;0m\2minishell\1\e[0m\2> "

/* ************************************************************************** */
/* LINES																	  */
/* ************************************************************************** */

typedef struct s_lines
{
	t_string	text;
	t_u32		cursor;
}	t_lines;

enum	e_prompt_error
{
	PROMPT_ERROR_MALLOC,
	PROMPT_ERROR_CTRL_C,
	PROMPT_ERROR_CTRL_D,
};

bool	alloc_lines(t_lines *lines);
bool	read_lines(t_lines *lines, const char *prompt,
			enum e_prompt_error *error);
void	register_command(t_lines lines);
void	cut_lines(t_lines *lines);
void	free_lines(t_lines lines);

/* ************************************************************************** */
/* TOKEN																	  */
/* ************************************************************************** */

enum	e_token_type
{
	TOKEN_OP,
	TOKEN_WORD,
};

typedef struct s_token
{
	enum e_token_type	type;
	t_str				content;
}	t_token;

bool	parse_token(t_lines *lines, t_token *token, const char *prompt,
			enum e_prompt_error *error);
void	print_token(t_token token);

/* ************************************************************************** */
/* TOKENIZER																  */
/* ************************************************************************** */

typedef struct s_tokenizer
{
	t_vector	tokens;
	t_lines		*lines;
}	t_tokenizer;

enum	e_syntax_error
{
	SYNTAX_ERROR_MALLOC,
	SYNTAX_ERROR_CTRL_C,
	SYNTAX_ERROR_CTRL_D,
	SYNTAX_ERROR_NO_MATCH,
};

bool	alloc_tokenizer(t_tokenizer *tokenizer, t_lines *lines);
bool	match_token(t_tokenizer *tokenizer, char *content, const char *prompt,
			enum e_syntax_error *error);
bool	peek_token(t_tokenizer *tokenizer, t_token *token, const char *prompt,
			enum e_prompt_error *error);
bool	consume_token(t_tokenizer *tokenizer, const char *prompt,
			enum e_prompt_error *error);
void	free_tokenizer(t_tokenizer tokenizer);

/* ************************************************************************** */
/* AST																		  */
/* ************************************************************************** */

enum e_exec_error
{
	EXEC_ERROR_EXIT,
	EXEC_ERROR_RECOVER,
};

typedef struct s_session	t_session;

enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND,
};

typedef struct s_redirection
{
	enum e_redir_type	type;
	union {
		t_string		filename;
		struct {
			t_string	delimiter;
			t_string	content;
		};
	};
}	t_redirection;

bool	parse_cmd_redir(t_vector *redirs, t_tokenizer *tokenizer,
			enum e_syntax_error *error);
bool	run_cmd_redirs(t_vector redirs, enum e_exec_error *error);

typedef struct s_simple_command
{
	t_vector	argv;
	t_vector	redirs;
}	t_simple_command;

bool	parse_cmd_arg(t_vector *argv, t_tokenizer *tokenizer,
			enum e_syntax_error *error);

bool	alloc_simple_command(t_simple_command *cmd);
bool	parse_simple_command(t_simple_command *cmd, t_tokenizer *tokenizer,
			enum e_syntax_error *error);
bool	run_simple_command(t_simple_command cmd, t_session *session,
			enum e_exec_error *error);
void	start_simple_command(t_simple_command cmd, t_session *session,
			enum e_exec_error *error);
void	free_simple_command(t_simple_command cmd);

bool	alloc_pipeline(t_vector *pipeline);
bool	parse_pipeline(t_vector *pipeline, t_tokenizer *tokenizer,
			enum e_syntax_error *error);
bool	run_pipeline(t_vector pipeline, t_session *session,
			enum e_exec_error *error);
void	free_pipeline(t_vector pipeline);

typedef struct s_ast_root
{
	t_vector	pipes;
}	t_ast_root;

bool	alloc_ast(t_ast_root *ast);
bool	parse_ast(t_ast_root *ast, t_lines *lines, enum e_syntax_error *error);
bool	run_ast(t_ast_root ast, t_session *session,
			enum e_exec_error *error);
void	free_ast(t_ast_root ast);

/* ************************************************************************** */
/* ENV																		  */
/* ************************************************************************** */

typedef struct s_env_var
{
	t_string	string;
	t_u32		eq_pos;
}	t_env_var;

bool	parse_env_var(t_env_var *var, t_str str);
t_str	get_env_var_name(t_env_var var);
t_str	get_env_var_value(t_env_var var);
bool	set_env_var_value(t_env_var *var, t_str value);
void	free_env_var(t_env_var var);

typedef struct s_env
{
	t_vector	vars;
}	t_env;

bool	parse_env(t_env *env, char **env_strs);
bool	get_env_var(t_env env, t_str name, t_str *value);
bool	set_env_var(t_env *env, t_str name, t_str value);
void	display_env(t_env *env);
void	free_env(t_env env);

/* ************************************************************************** */
/* BACKUP_FDS																  */
/* ************************************************************************** */

typedef struct s_backup_fds
{
	t_i32	stdin;
	t_i32	stdout;
}	t_backup_fds;

bool	save_backup_fds(t_backup_fds *backup);
bool	restore_backup_fds(t_backup_fds backup);
void	discard_backup_fds(t_backup_fds backup);

/* ************************************************************************** */
/* EXECUTABLE																  */
/* ************************************************************************** */

typedef struct s_executable
{
	t_string	full_path;
	t_vector	compact_argv;
	t_vector	compact_env;
}	t_executable;

bool	find_executable(t_env env, t_str cmd_name, t_string *full_path,
			enum e_exec_error *error);
bool	alloc_executable(t_executable *exec, t_vector argv, t_env env,
			enum e_exec_error *error);
bool	run_executable(t_executable exec, t_backup_fds backup,
			t_u8 *status, enum e_exec_error *error);
void	start_executable(t_executable exec);
void	free_executable(t_executable exec);

bool	run_raw_command(t_vector argv, t_session *session,
			t_backup_fds backup, enum e_exec_error *error);
bool	start_raw_command(t_vector argv, t_session *session,
			enum e_exec_error *error);

/* ************************************************************************** */
/* SESSION																	  */
/* ************************************************************************** */

// also contains terminal settings?

typedef struct s_session
{
	t_lines		lines;
	t_env		env;
	t_u8		last_status;
}	t_session;

bool	init_session(t_session *session, char **env);
bool	run_repl(t_session *session);
void	destroy_session(t_session session);

/* ************************************************************************** */
/* UTILS																	  */
/* ************************************************************************** */

bool	move_fd(int from, int to);
bool	ft_fork(pid_t *pid);

#endif