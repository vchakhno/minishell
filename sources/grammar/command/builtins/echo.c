/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/14 17:45:49 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static bool	echo_check_n_option(t_str arg)
{
	t_u32	i;

	if (arg.len <= 1 || arg.c_str[0] != '-')
		return (false);
	i = 1;
	while (i < arg.len)
	{
		if (arg.c_str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

bool	run_builtin_echo(t_vector argv, t_env *env, t_u8 *exit_status)
{
	t_u32	i;
	bool	n_option;

	(void) env;
	n_option = (argv.size >= 2
			&& echo_check_n_option(((t_string *)argv.elems)[1].str));
	i = 1 + n_option;
	while (i < argv.size)
	{
		ft_printf("{str}", ((t_string *)argv.elems)[i].str);
		if (i != argv.size - 1)
			ft_printf(" ");
		i++;
	}
	if (!n_option)
		ft_println("");
	return (builtin_ok(exit_status));
}
