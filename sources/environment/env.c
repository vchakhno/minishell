/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:13:01 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/29 08:03:33 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			free_env(*env);
			return (false);
		}
		ft_vector_push(&env->vars, &var);
		i++;
	}
	return (true);
}

void	display_env(t_env *env)
{
	t_env_var	var;
	t_u32		i;

	i = 0;
	while (i < env->vars.size)
	{
		var = ((t_env_var *)env->vars.elems)[i];
		ft_println("name: \"{str}\", value: \"{str}\"",
			get_env_var_name(var),
			get_env_var_value(var));
		i++;
	}
}

void	free_env(t_env env)
{
	t_u32	i;

	i = 0;
	while (i < env.vars.size)
	{
		free_env_var(((t_env_var *)env.vars.elems)[i]);
		i++;
	}
	ft_vector_free(env.vars);
}
