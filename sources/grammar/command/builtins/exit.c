/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 07:44:36 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

static bool	parse_exit_status(char *str, t_u8 *exit_status)
{
	t_u8	val;

	val = str[0] - '0';
	if (str[1])
		val = val * 10 + str[1] - '0';
	if (str[1] && str[2])
	{
		if (val > (255 - str[2] + '0') / 10)
			return (false);
		val = val * 10 + str[2] - '0';
	}
	*exit_status = val;
	return (true);
}

static bool	parse_exit_arg(t_str arg, t_u8 *exit_status)
{
	if (arg.len == 0)
	{
		print_error("exit: The argument is empty");
		return (false);
	}
	if (!ft_str_is_digit(arg))
	{
		print_error("exit: `{str}` is not a number "
			"(it contains symbols other than digits)", arg);
		return (false);
	}
	if (arg.len > 1 && *arg.c_str == '0')
	{
		print_error("exit: `{str}` contains leading zeros", arg);
		return (false);
	}
	if (!parse_exit_status(arg.c_str, exit_status))
	{
		print_error("exit: `{str}` is not between 0 and 255", arg);
		return (false);
	}
	return (true);
}

bool	run_builtin_exit(t_vector argv, t_env *env, t_u8 *exit_status)
{
	(void) env;
	if (argv.size > 2)
	{
		print_error("exit: Too many arguments, expected one");
		return (builtin_error(exit_status));
	}
	if (argv.size == 1)
		*exit_status = 0;
	else
	{
		if (!parse_exit_arg(((t_string *)argv.elems)[1].str, exit_status))
			return (builtin_error(exit_status));
	}
	ft_eprintln("exit");
	return (false);
}
