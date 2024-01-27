/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compact.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:23:46 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 00:27:37 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executable.h"
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <unistd.h>

bool	compact_argv(t_vector *compact_argv, t_vector argv)
{
	t_u32	i;

	if (!ft_vector_alloc(compact_argv, sizeof(char *), argv.size + 1))
		return (false);
	i = 0;
	while (i < argv.size)
	{
		ft_vector_push(compact_argv, &((t_string *)argv.elems)[i].c_str);
		i++;
	}
	ft_vector_push(compact_argv, &(char *){NULL});
	return (true);
}

bool	compact_env(t_vector *compact_env, t_env env)
{
	t_env_var	var;
	t_u32		i;

	if (!ft_vector_alloc(compact_env, sizeof(char *), env.vars.size + 1))
		return (false);
	i = 0;
	while (i < env.vars.size)
	{
		var = ((t_env_var *)env.vars.elems)[i];
		ft_vector_push(compact_env, &var.string.c_str);
		i++;
	}
	ft_vector_push(compact_env, &(char *){NULL});
	return (true);
}
