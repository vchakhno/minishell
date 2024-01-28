/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 07:18:39 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

static bool	check_args(t_u32 argc)
{
	if (argc == 1)
	{
		print_error("cd: No path argument");
		return (false);
	}
	if (argc > 2)
	{
		print_error("cd: Too many arguments");
		return (false);
	}
	return (true);
}

static bool	change_dir(char *path)
{
	if (chdir(path) == -1)
	{
		print_error("cd: {c_str}", strerror(errno));
		return (false);
	}
	return (true);
}

static bool	update_oldpwd(t_env *env)
{
	t_str	old_path;

	if (!get_env_var(*env, ft_str("PWD"), &old_path))
		return (true);
	if (!set_env_var(env, ft_str("OLDPWD"), old_path))
		return (false);
	return (true);
}

static bool	update_pwd(t_env *env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (false);
	if (!set_env_var(env, ft_str("PWD"), ft_str(path)))
	{
		free(path);
		return (false);
	}
	free(path);
	return (true);
}

bool	run_builtin_cd(t_vector argv, t_env *env, t_u8 *exit_status)
{
	if (!check_args(argv.size))
		return (builtin_error(exit_status));
	if (!change_dir(((t_string *)argv.elems)[1].c_str))
		return (builtin_error(exit_status));
	if (!update_oldpwd(env) || !update_pwd(env))
		return (builtin_error(exit_status));
	return (builtin_ok(exit_status));
}
