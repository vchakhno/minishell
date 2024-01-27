/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 00:20:32 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "environment.h"
# include <stdbool.h>
# include <libft/libft.h>

/* ************************************************************************** */
/* EXPAND																	  */
/* ************************************************************************** */

typedef struct s_fields
{
	t_vector	*fields;
	bool		open;
}	t_fields;

// args
bool	expand_args(t_vector strings, t_env env, t_u8 exit_status,
			t_vector *fields);

// fields
void	init_fields(t_fields *fields, t_vector *fields_vec);
bool	add_field(t_fields *fields, t_str field);
bool	add_u8_field(t_fields *fields, t_u8 field);
void	close_field(t_fields *fields);
void	free_fields_vec(t_vector fields);

// quotes
bool	consume_until(t_str *str, char *delim, t_fields *fields);
bool	consume_quotes(t_str *str, t_fields *fields);
bool	expand_dquotes(t_str *str, t_env env, t_u8 exit_status,
			t_fields *fields);

// redir
bool	expand_redir(t_str filename, t_env env, t_u8 exit_status,
			t_string *field);

// utils
void	advance_str(t_str *str, t_u32 n);
bool	string_append_char(t_string *string, char c);

// var
bool	expand_split_var(t_str *src, t_env env, t_u8 exit_status,
			t_fields *fields);
bool	expand_var(t_str *src, t_env env, t_u8 exit_status,
			t_fields *fields);

#endif