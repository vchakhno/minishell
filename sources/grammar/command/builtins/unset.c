/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/30 03:43:25 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

bool	run_builtin_unset(t_vector argv, t_env *env, t_u8 *exit_status)
{
	if (argv.size > 2)
	{
		print_error("unset: too many arguments");
		return (builtin_error(exit_status));
	}
	if (argv.size == 1)
	{
		print_error("unset: variable name expected");
		return (builtin_error(exit_status));
	}
	remove_env_var(env, ((t_string *)argv.elems)[1].str);
	return (builtin_ok(exit_status));
}
