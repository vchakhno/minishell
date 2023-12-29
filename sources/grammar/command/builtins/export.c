/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/29 08:11:07 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

static void	display_exports(t_env env)
{
	(void) env;
	ft_println("Not implemented");
}

bool	export_var(t_env *env, t_str arg)
{
	t_u32	eq_pos;

	if (ft_str_find_c_str(arg, "=", &eq_pos))
	{
		return (set_env_var(env, ft_str_get_slice(arg, 0, eq_pos),
				ft_str_get_slice(arg, eq_pos + 1, arg.len - 1 - eq_pos)));
	}
	else
	{
		return (set_env_var(env, ft_str_get_slice(arg, 0, eq_pos), ft_str("")));
	}
}

bool	run_builtin_export(t_vector argv, t_session *session)
{
	t_u32	i;

	if (argv.size == 0)
	{
		display_exports(session->env);
		return (true);
	}
	i = 1;
	while (i < argv.size)
	{
		if (!export_var(&session->env, ((t_string *)argv.elems)[i].str))
			return (false);
		i++;
	}
	return (true);
}
