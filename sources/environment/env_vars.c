/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:13:01 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/29 08:26:41 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_env_var(t_env env, t_str name, t_str *value)
{
	t_env_var	var;
	t_u32		i;

	i = 0;
	while (i < env.vars.size)
	{
		var = ((t_env_var *)env.vars.elems)[i];
		if (ft_str_equal_str(get_env_var_name(var), name))
		{
			*value = get_env_var_value(var);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	set_env_var(t_env *env, t_str name, t_str value)
{
	t_env_var	*var;
	t_u32		i;
	t_env_var	new_var;

	i = 0;
	while (i < env->vars.size)
	{
		var = &((t_env_var *)env->vars.elems)[i];
		if (ft_str_equal_str(get_env_var_name(*var), name))
			return (set_env_var_value(var, value));
		i++;
	}
	if (!ft_vector_reserve(&env->vars, 1)
		|| !ft_string_alloc(&new_var.string, name.len + value.len + 2))
		return (false);
	ft_string_append_str(&new_var.string, name);
	ft_string_append_c_str(&new_var.string, "=");
	ft_string_append_str(&new_var.string, value);
	new_var.eq_pos = name.len;
	ft_vector_push(&env->vars, &new_var);
	return (true);
}

void	remove_env_var(t_env *env, t_str name)
{
	t_env_var	*var;
	t_u32		i;

	i = 0;
	while (i < env->vars.size)
	{
		var = &((t_env_var *)env->vars.elems)[i];
		if (ft_str_equal_str(get_env_var_name(*var), name))
		{
			ft_vector_remove(&env->vars, i, NULL);
			return ;
		}
		i++;
	}
}
