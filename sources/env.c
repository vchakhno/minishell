/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:13:01 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 14:50:10 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_env_var(t_env_var *var, t_str str)
{
	t_u32	sep;

	if (!ft_str_find_char(str, '=', &sep))
		return (false);
	if (!ft_string_from_str(&var->name, ft_str_get_slice(str, 0, sep)))
		return (false);
	if (!ft_string_from_str(&var->value,
			ft_str_get_slice(str, sep + 1, str.len - sep - 1)))
	{
		ft_string_free(var->name);
		return (false);
	}
	return (true);
}

bool	parse_env(t_env *env, char **env_strs)
{
	t_u32		len;
	t_u32		i;
	t_env_var	var;

	len = 0;
	while (env_strs[len])
		len++;
	if (!ft_vector_alloc(&env->vars, sizeof(t_env_var), len))
		return (false);
	i = 0;
	while (env_strs[i])
	{
		if (!parse_env_var(&var, ft_str(env_strs[i])))
		{
			free_env(env);
			return (false);
		}
		ft_vector_push(&env->vars, &var);
		i++;
	}
	return (true);
}

bool	get_env_var(t_env *env, t_str name, t_str *value)
{
	t_u32	i;

	i = 0;
	while (i < env->vars.size)
	{
		if (ft_str_equal_str(((t_env_var *)env->vars.elems)[i].name.str, name))
		{
			*value = ((t_env_var *)env->vars.elems)[i].value.str;
			return (true);
		}
		i++;
	}
	return (false);
}

void	display_env(t_env *env)
{
	t_u32	i;

	i = 0;
	while (i < env->vars.size)
	{
		ft_println("name: \"{str}\", value: \"{str}\"",
			((t_env_var *)env->vars.elems)[i].name.str,
			((t_env_var *)env->vars.elems)[i].value.str);
		i++;
	}
}

void	free_env_var(t_env_var *var)
{
	ft_string_free(var->name);
	ft_string_free(var->value);
}

void	free_env(t_env *env)
{
	t_u32	i;

	i = 0;
	while (i < env->vars.size)
	{
		free_env_var(&((t_env_var *)env->vars.elems)[i]);
		i++;
	}
	ft_vector_free(env->vars);
}
