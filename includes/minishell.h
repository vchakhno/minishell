/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/11 11:25:45 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>
# include <libft/libft.h>

# define PROMPT "\033[38;2;255;63;0mminishell\e[0m> "
/* ************************************************************************** */
/* ENV																		  */
/* ************************************************************************** */

typedef struct s_env_item
{
	t_string	key;
	t_string	value;
}	t_env_item;

typedef struct s_env
{
	t_vector	items;
}	t_env;

bool	parse_env(t_env *env, char **env_strs);
void	display_env(t_env *env);
void	free_env(t_env *env);

/* ************************************************************************** */
/* TOKENS																	  */
/* ************************************************************************** */

typedef struct s_program t_program;

enum e_token_type
{
	TOKEN_PUNCT,
	TOKEN_IDENT,
};

typedef struct s_token
{
	enum e_token_type	type; 
	t_str				content;
}	t_token;

bool	parse_token(t_token *token, t_program *program);
bool	peek_token(t_vector *tokens, t_token *token, t_program *program);
bool	match_token(
			t_vector *tokens, char *str, t_program *program, bool *matches);

/* ************************************************************************** */
/* AST																		  */
/* ************************************************************************** */

typedef struct s_session	t_session;

enum e_ast_redir_type
{
	AST_REDIR_IN,
	AST_REDIR_OUT,
};

typedef struct s_ast_redirection
{
	enum e_ast_redir_type	type;
	t_string				filename;
}	t_ast_redirection;

typedef struct s_ast_command
{
	t_vector	argv;
	t_vector	redirs;
}	t_ast_command;

typedef struct s_ast
{
	t_vector	pipes;
}	t_ast;

bool	parse_ast(t_ast *ast, t_program *program);
bool	execute_ast(t_ast ast, t_session *session);
void	free_ast(t_ast ast);

/* ************************************************************************** */
/* PROGRAM																	  */
/* ************************************************************************** */

typedef struct s_program
{
	t_string	text;
	t_u32		cmd_cursor;
}	t_program;

bool	alloc_program(t_program *program);
bool	get_program(t_program *program, char *prompt);
void	register_command(t_program program);
void	cut_program(t_program *program);
void	free_program(t_program program);

/* ************************************************************************** */
/* SESSION																	  */
/* ************************************************************************** */

typedef struct s_session
{
	t_env	env;
	bool	should_exit;
}	t_session;

bool	init_session(t_session *session, char **env);
bool	run_repl(t_session *session);
void	destroy_session(t_session *session);

#endif