/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:23:46 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/23 17:30:53 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

bool	get_builtin(t_str name, t_builtin *builtin_func)
{
	char *const		builtin_names[] = {
		"exit", "cd", "pwd", "export", "_cat"
	};
	const t_builtin	builtin_funcs[] = {
		run_builtin_exit, run_builtin_cd, run_builtin_pwd, run_builtin_export,
		run_builtin_cat
	};
	t_u32			i;

	i = 0;
	while (i < (t_u32) sizeof builtin_names / sizeof * builtin_names)
	{
		if (ft_str_equal_c_str(name, builtin_names[i]))
		{
			*builtin_func = builtin_funcs[i];
			return (true);
		}
		i++;
	}
	return (false);
}

bool	run_raw_command(
	t_vector argv, t_session *session, t_backup_fds backup,
	enum e_exec_error *error
) {
	t_executable	exec;
	t_builtin		builtin_func;

	if (get_builtin(((t_string *)argv.elems)[0].str, &builtin_func))
		return (builtin_func(argv, session, error));
	if (!alloc_executable(&exec, argv, session->env, error))
		return (false);
	if (!run_executable(exec, backup, &session->last_status, error))
	{
		free_executable(exec);
		return (false);
	}
	free_executable(exec);
	return (true);
}

bool	start_raw_command(
	t_vector argv, t_session *session, enum e_exec_error *error
) {
	t_executable	exec;

	if (!alloc_executable(&exec, argv, session->env, error))
		return (false);
	start_executable(exec);
	free_executable(exec);
	*error = EXEC_ERROR_EXIT;
	return (false);
}
