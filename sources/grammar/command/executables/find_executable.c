/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:04:56 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 11:39:28 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executable.h"
#include "utils.h"
#include <unistd.h>

bool	join_path(t_str path_prefix, t_str cmd_name, t_string *full_path)
{
	if (!ft_string_alloc(full_path, path_prefix.len + cmd_name.len + 2))
		return (false);
	ft_string_append_str(full_path, path_prefix);
	ft_string_append_c_str(full_path, "/");
	ft_string_append_str(full_path, cmd_name);
	return (true);
}

bool	check_executable_at(t_str path, bool *found)
{
	if (access(path.c_str, F_OK) == -1)
		return (false);
	*found = true;
	if (access(path.c_str, X_OK) == -1)
		return (false);
	return (true);
}

bool	find_executable_in_path(
	t_str path_var, t_str cmd_name, t_string *full_path,
	t_u8 *exit_status
) {
	t_str		path_prefix;
	t_str_iter	path_iter;
	bool		found;

	found = false;
	path_iter = ft_str_split_by_c_str(path_var, ":");
	while (path_iter.next(&path_iter, &path_prefix))
	{
		if (!join_path(path_prefix, cmd_name, full_path))
			return (false);
		if (check_executable_at(full_path->str, &found))
			return (true);
		ft_string_free(*full_path);
	}
	if (!found)
		print_error("`{str}`: Command not found", cmd_name);
	else
		print_error("`{str}`: Permission denied", cmd_name);
	*exit_status = 127 - found;
	return (false);
}

bool	find_executable_in_cwd(
	t_str cmd_name, t_string *full_path, t_u8 *exit_status
) {
	if (!ft_string_from_str(full_path, cmd_name))
	{
		*exit_status = 1;
		return (false);
	}
	if (access(full_path->c_str, F_OK) == -1)
	{
		*exit_status = 127;
		print_error("`{str}`: Command not found", cmd_name);
		return (false);
	}
	if (access(full_path->c_str, X_OK) == -1)
	{
		*exit_status = 126;
		print_error("`{str}`: Permission denied", cmd_name);
		return (false);
	}
	return (true);
}

bool	find_executable(
	t_env env, t_str cmd_name, t_string *full_path, t_u8 *exit_status
) {
	t_str	path_var;

	if (ft_str_contains_c_str(cmd_name, "/"))
		return (find_executable_in_cwd(cmd_name, full_path, exit_status));
	if (!get_env_var(env, ft_str("PATH"), &path_var))
	{
		print_error("{str}: PATH is unset", cmd_name);
		*exit_status = 127;
		return (false);
	}
	return (
		find_executable_in_path(path_var, cmd_name, full_path, exit_status)
	);
}
