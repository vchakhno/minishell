/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 07:10:51 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "environment.h"
# include <stdbool.h>
# include <libft/libft.h>

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

#endif