/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/23 01:06:46 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	parse_exit_status(char *str, t_u8 *exit_status)
{
	t_u8	val;

	val = str[0] - '0';
	if (str[1])
		val = val * 10 + str[1] - '0';
	if (str[1] && str[2])
	{
		if (val >= (256 - str[2] + '0') / 10)
			return (false);
		val = val * 10 + str[1] - '0';
	}
	*exit_status = val;
	return (true);
}

static bool	validate_exit_arg(t_str arg, t_u8 *exit_status)
{
	if (arg.len == 0)
	{
		print_error("exit: the argument is empty");
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

bool	run_builtin_exit(
	t_vector argv, t_session *session, enum e_exec_error *error
) {
	(void) error;
	if (argv.size > 2)
	{
		print_error("exit: too many arguments");
		return (true);
	}
	if (argv.size == 1)
		session->last_status = 0;
	else
	{
		if (!validate_exit_arg(((t_string *)argv.elems)[1].str,
			&session->last_status))
			return (true);
	}
	ft_eprintln("exit");
	session->should_exit = true;
	return (true);
}
