/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/19 21:54:15 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>
# include <libft/libft.h>

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
	t_string			filename;
}	t_redirection;

typedef struct s_cmd_ast
{
	t_vector	argv;
	t_vector	redirs;
}	t_cmd_ast;

bool	alloc_cmd_ast(t_cmd_ast *ast);
bool	parse_cmd_redir(t_cmd_ast *ast, t_tokenizer *tokenizer,
			enum e_syntax_error *error);
bool	parse_cmd_ast(t_cmd_ast *ast, t_tokenizer *tokenizer,
			enum e_syntax_error *error);
bool	execute_cmd_ast(t_cmd_ast ast, t_session *session,
			enum e_exec_error *error);
void	free_cmd_ast(t_cmd_ast ast);

typedef struct s_pipe_ast
{
	t_vector	pipes;
}	t_pipe_ast;

bool	alloc_pipe_ast(t_pipe_ast *ast);
bool	parse_pipe_ast(t_pipe_ast *ast, t_tokenizer *tokenizer,
			enum e_syntax_error *error);
bool	execute_pipe_ast(t_pipe_ast ast, t_session *session,
			enum e_exec_error *error);
void	free_pipe_ast(t_pipe_ast ast);

typedef struct s_ast_root
{
	t_pipe_ast	pipes;
}	t_ast_root;

bool	alloc_ast(t_ast_root *ast);
bool	parse_ast(t_ast_root *ast, t_lines *lines, enum e_syntax_error *error);
bool	execute_ast(t_ast_root ast, t_session *session,
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
/* EXECUTABLE																  */
/* ************************************************************************** */

typedef struct s_executable
{
	t_string	full_path;
	t_vector	compact_argv;
	t_vector	compact_env;
}	t_executable;

bool	search_path(t_env env, t_str cmd_name, t_string *full_path,
			enum e_exec_error *error);
bool	alloc_executable(t_executable *exec, t_vector argv, t_env env,
			enum e_exec_error *error);
bool	run_executable(t_executable exec, enum e_exec_error *error);
void	free_executable(t_executable exec);

/* ************************************************************************** */
/* SESSION																	  */
/* ************************************************************************** */

// also contains history and terminal settings

typedef struct s_session
{
	t_env	env;
	bool	should_exit;
	t_u8	last_status;
}	t_session;

bool	init_session(t_session *session, char **env);
bool	run_repl(t_session *session);
void	destroy_session(t_session session);

#endif