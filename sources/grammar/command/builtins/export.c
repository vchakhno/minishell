/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 08:04:45 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

bool	check_var_name(t_str name)
{
	t_u32	i;

	if (name.len == 0
		|| (!ft_char_is_alpha(name.c_str[0]) && name.c_str[0] != '_'))
		return (false);
	i = 1;
	while (i < name.len
		&& (ft_char_is_alnum(name.c_str[i]) || name.c_str[i] == '_'))
		i++;
	return (i == name.len);
}

bool	export_var(t_env *env, t_str arg)
{
	t_str	name;
	t_str	value;
	t_u32	eq_pos;

	if (ft_str_find_c_str(arg, "=", &eq_pos))
	{
		name = ft_str_get_slice(arg, 0, eq_pos);
		value = ft_str_get_slice(arg, eq_pos + 1, arg.len - 1 - eq_pos);
	}
	else
	{
		name = arg;
		value = ft_str("");
	}
	if (!check_var_name(name))
	{
		print_error("env: `{str}` is not a valid variable name", name);
		return (false);
	}
	return (set_env_var(env, name, value));
}

bool	run_builtin_export(t_vector argv, t_env *env, t_u8 *exit_status)
{
	t_u32	i;

	if (argv.size == 1)
	{
		print_error("export: Export without arguments is undefined "
			"according to POSIX");
		return (builtin_ok(exit_status));
	}
	i = 1;
	while (i < argv.size)
	{
		if (!export_var(env, ((t_string *)argv.elems)[i].str))
			return (builtin_error(exit_status));
		i++;
	}
	return (builtin_ok(exit_status));
}
