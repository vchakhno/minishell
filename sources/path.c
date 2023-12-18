/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:04:56 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 15:47:25 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

bool	search_path(t_env *env, t_str cmd_name, t_string *full_path)
{
	t_str		path_var;
	t_str		path_prefix;
	t_str_iter	path_iter;

	if (!get_env_var(env, ft_str("PATH"), &path_var))
		return (false);
	if (!ft_string_alloc(full_path, 64))
		return (false);
	path_iter = ft_str_split_by_c_str(path_var, ":");
	while (path_iter.next(&path_iter, &path_prefix))
	{
		full_path->len = 0;
		if (!ft_string_reserve(full_path, path_prefix.len + cmd_name.len + 1))
		{
			ft_string_free(*full_path);
			return (false);
		}
		ft_string_append_str(full_path, path_prefix);
		ft_string_append_c_str(full_path, "/");
		ft_string_append_str(full_path, cmd_name);
		if (access(full_path->c_str, X_OK) == 0)
			return (true);
	}
	ft_string_free(*full_path);
	return (false);
}
