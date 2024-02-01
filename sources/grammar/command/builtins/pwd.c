/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 04:08:21 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

bool	run_builtin_pwd(t_vector argv, t_env *env, t_u8 *exit_status)
{
	char	*path;

	(void) env;
	if (argv.size == 1)
	{
		print_error("pwd: No arguments expected");
		return (builtin_error(exit_status));
	}
	path = getcwd(NULL, 0);
	if (!path)
	{
		print_error("{c_str}", strerror(errno));
		return (builtin_error(exit_status));
	}
	ft_println("{c_str}", path);
	free(path);
	clear_stdout();
	return (builtin_ok(exit_status));
}
