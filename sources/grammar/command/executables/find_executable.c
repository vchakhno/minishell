/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:04:56 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/19 23:26:51 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

bool	join_path(t_str path_prefix, t_str cmd_name, t_string *full_path)
{
	full_path->len = 0;
	if (!ft_string_reserve(full_path, path_prefix.len + cmd_name.len + 1))
		return (false);
	ft_string_append_str(full_path, path_prefix);
	ft_string_append_c_str(full_path, "/");
	ft_string_append_str(full_path, cmd_name);
	return (true);
}

bool	find_executable_in_path(
	t_str path_var, t_str cmd_name, t_string *full_path,
	enum e_exec_error *error
) {
	t_str		path_prefix;
	t_str_iter	path_iter;

	if (!ft_string_alloc(full_path, 64))
	{
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
	path_iter = ft_str_split_by_c_str(path_var, ":");
	while (path_iter.next(&path_iter, &path_prefix))
	{
		if (!join_path(path_prefix, cmd_name, full_path))
		{
			*error = EXEC_ERROR_EXIT;
			return (false);
		}
		if (access(full_path->c_str, X_OK) == 0)
		{
			*error = EXEC_ERROR_RECOVER;
			return (true);
		}
	}
	ft_string_free(*full_path);
	*error = EXEC_ERROR_RECOVER;
	return (false);
}

bool	find_executable_in_cwd(
	t_str cmd_name, t_string *full_path, enum e_exec_error *error
) {
	if (!ft_string_from_str(full_path, cmd_name))
	{
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
	if (access(full_path->c_str, X_OK) == -1)
	{
		*error = EXEC_ERROR_RECOVER;
		return (false);
	}
	return (true);
}

bool	find_executable(
	t_env env, t_str cmd_name, t_string *full_path, enum e_exec_error *error
) {
	t_str	path_var;

	if (ft_str_contains_c_str(cmd_name, "/"))
		return (find_executable_in_cwd(cmd_name, full_path, error));
	if (!get_env_var(env, ft_str("PATH"), &path_var))
	{
		*error = EXEC_ERROR_RECOVER;
		return (false);
	}
	return (find_executable_in_path(path_var, cmd_name, full_path, error));
}
