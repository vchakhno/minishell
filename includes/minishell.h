/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/30 02:18:24 by vchakhno         ###   ########.fr       */
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
# define ERROR_PROMPT "minishell: "

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

bool	read_input(t_string *new_lines, const char *prompt,
			enum e_prompt_error *error);

bool	alloc_lines(t_lines *lines);
bool	append_lines(t_lines *lines, const char *prompt,
			enum e_prompt_error *error);
bool	read_line(t_lines *lines, t_str *line, const char *prompt,
			enum e_prompt_error *error);
void	register_command(t_lines lines);
void	cut_lines(t_lines *lines);
void	free_lines(t_lines lines);

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

bool	parse_token(t_lines *lines, t_token *token, const char *prompt,
			enum e_prompt_error *error);
t_str	get_token_content(t_lines lines, t_token token);
void	print_token(t_lines lines, t_token token);

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
bool	match_word_token(t_tokenizer *tokenizer, t_str *content,
			const char *prompt, enum e_syntax_error *error);
bool	peek_token(t_tokenizer *tokenizer, t_token *token, const char *prompt,
			enum e_prompt_error *error);
bool	tokenize_line(t_tokenizer *tokenizer, const char *prompt,
			enum e_prompt_error *error);
bool	consume_token(t_tokenizer *tokenizer, const char *prompt,
			enum e_prompt_error *error);
void	free_tokenizer(t_tokenizer tokenizer);

/* ************************************************************************** */
/* REDIRECTIONS																  */
/* ************************************************************************** */

enum e_exec_error
{
	EXEC_ERROR_EXIT,
	EXEC_ERROR_RECOVER,
};

typedef struct s_output_redir
{
	t_string	filename;
}	t_output_redir;

bool	parse_output_redir(t_output_redir *redir, t_tokenizer *tokenizer,
			enum e_syntax_error *error);
bool	run_output_redir(t_output_redir *redir);
void	free_output_redir(t_output_redir redir);

typedef struct s_append_redir
{
	t_string	filename;
}	t_append_redir;

bool	parse_append_redir(t_append_redir *redir, t_tokenizer *tokenizer,
			enum e_syntax_error *error);
bool	run_append_redir(t_append_redir *redir);
void	free_append_redir(t_append_redir redir);

typedef struct s_input_redir
{
	t_string	filename;
}	t_input_redir;

bool	parse_input_redir(t_input_redir *redir, t_tokenizer *tokenizer,
			enum e_syntax_error *error);
bool	run_input_redir(t_input_redir *redir);
void	free_input_redir(t_input_redir redir);

typedef struct s_heredoc
{
	t_string	delimiter;
	t_string	body;
	pid_t		pid;
}	t_heredoc;

bool	parse_heredoc(t_heredoc *heredoc, t_tokenizer *tokenizer,
			enum e_syntax_error *error);
bool	run_heredoc(t_heredoc *heredoc, enum e_exec_error *error);
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

bool	run_redirection(t_redirection *redir, enum e_exec_error *error);
bool	parse_redirection(t_redirection *redir, t_tokenizer *tokenizer,
			enum e_syntax_error *error);
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
		enum e_syntax_error *error);
bool	run_redirections(t_vector redirs, t_backup_fds *backup,
			enum e_exec_error *error);
void	cleanup_redirections(t_vector redirs, t_backup_fds backup, t_u32 size);

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
			enum e_syntax_error *error);

bool	alloc_simple_command(t_simple_command *cmd);
bool	parse_simple_command(t_simple_command *cmd, t_tokenizer *tokenizer,
			enum e_syntax_error *error);
bool	run_simple_command(t_simple_command *cmd, t_session *session,
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

bool	get_env_var(t_env env, t_str name, t_str *value);
bool	set_env_var(t_env *env, t_str name, t_str value);
void	remove_env_var(t_env *env, t_str name);

bool	parse_env(t_env *env, char **env_strs);
void	display_env(t_env *env);
void	free_env(t_env env);

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
void	free_executable(t_executable exec);

bool	run_raw_command(t_vector argv, t_session *session,
			t_backup_fds backup, enum e_exec_error *error);

/* ************************************************************************** */
/* SESSION																	  */
/* ************************************************************************** */

// also contains terminal settings?

typedef struct s_session
{
	t_lines		lines;
	t_env		env;
	t_u8		exit_status;
	bool		should_exit;
}	t_session;

bool	init_session(t_session *session, char **env);
bool	run_repl(t_session *session);
void	destroy_session(t_session session);

/* ************************************************************************** */
/* UTILS																	  */
/* ************************************************************************** */

bool	move_fd(int from, int to);
bool	ft_fork(pid_t *pid);
void	print_error(char *error, ...);

/* ************************************************************************** */
/* BUILTINS																	  */
/* ************************************************************************** */

typedef bool				(*t_builtin)(
	t_vector argv, t_env *env, t_u8 *exit_status
);

bool	builtin_ok(t_u8 *exit_status);
bool	builtin_error(t_u8 *exit_status);

bool	run_builtin_echo(t_vector argv, t_env *env, t_u8 *exit_status);
bool	run_builtin_cd(t_vector argv, t_env *env, t_u8 *exit_status);
bool	run_builtin_pwd(t_vector argv, t_env *env, t_u8 *exit_status);
bool	run_builtin_export(t_vector argv, t_env *env, t_u8 *exit_status);
bool	run_builtin_unset(t_vector argv, t_env *env, t_u8 *exit_status);
bool	run_builtin_env(t_vector argv, t_env *env, t_u8 *exit_status);
bool	run_builtin_exit(t_vector argv, t_env *env, t_u8 *exit_status);
bool	run_builtin_cat(t_vector argv, t_env *env, t_u8 *exit_status);

/* ************************************************************************** */
/* EXPAND																	  */
/* ************************************************************************** */

bool	expand_vars(char **cursor, t_env env, t_string *open_field,
			char *delim);
bool	expand(t_str str, t_env env, t_vector *closed_fields);
bool	expand_all(t_vector strings, t_env env, t_vector *fields);
void	free_fields(t_vector fields);

#endif