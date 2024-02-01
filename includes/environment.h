/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 01:17:59 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdbool.h>
# include <libft/libft.h>

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
void	display_env(t_env env);
void	free_env(t_env env);

#endif