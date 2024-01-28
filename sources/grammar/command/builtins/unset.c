/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 09:03:25 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"
#include <unistd.h>

bool	run_builtin_unset(t_vector argv, t_env *env, t_u8 *exit_status)
{
	t_str	name;

	if (argv.size > 2)
	{
		print_error("unset: Too many arguments, expected one");
		return (builtin_error(exit_status));
	}
	if (argv.size == 1)
	{
		print_error("unset: Variable name expected");
		return (builtin_error(exit_status));
	}
	name = ((t_string *)argv.elems)[1].str;
	if (!check_var_name(name))
	{
		print_error("unset: `{str}` is not a valid variable name", name);
		return (builtin_error(exit_status));
	}
	remove_env_var(env, name);
	return (builtin_ok(exit_status));
}
