/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/10 18:03:56 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>
# include <libft/libft.h>

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

/* ************************************************************************** */
/* AST																		  */
/* ************************************************************************** */

typedef struct s_ast
{
	
}	t_ast;

/* ************************************************************************** */
/* COMMAND																	  */
/* ************************************************************************** */

typedef struct s_session t_session;
typedef struct s_program t_program;

typedef struct s_command
{
	t_str		text;
	t_vector	tokens;
	t_u32		tokens_pos; // or a queue
	t_ast		tree;
}	t_command;

// calls the tokenizer to get tokens
// the tokenizer calls the program to get its contents
// the program calls readline to read user input
bool	parse_command(t_command *command, t_program *program);
void	register_command(t_command command);
bool	execute_command(t_command *command, t_session *session);
void	free_command(t_command command);

/* ************************************************************************** */
/* PROGRAM																	  */
/* ************************************************************************** */

typedef struct s_program
{
	t_string	str;
}	t_program;

bool	alloc_program(t_program *program);
bool	get_program(t_program *program, char *prompt);
void	cut_program(t_program *program, t_command command);
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