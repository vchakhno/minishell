/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/01 01:49:23 by vchakhno         ###   ########.fr       */
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
/* PROGRAM																	  */
/* ************************************************************************** */

typedef struct s_program
{
	t_string	str;
	t_u32		cursor;
}	t_program;

bool	alloc_program(t_program *program);
bool	get_program(t_program *program, char *prompt);
void	free_program(t_program program);

/* ************************************************************************** */
/* REPL_INPUT																  */
/* ************************************************************************** */

typedef struct s_repl_tokens
{
	t_vector	tokens;
	t_u32		pos;
}	t_repl_tokens;

bool	alloc_repl_tokens(t_repl_tokens *tokens);
bool	wait_repl_tokens(t_repl_tokens *tokens);
void	free_repl_tokens(t_repl_tokens tokens);

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

#endif