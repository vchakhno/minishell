/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:23:46 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 07:16:50 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"
#include "executable.h"
#include "builtins.h"
#include <stdio.h>

bool	get_builtin(t_str name, t_builtin *builtin_func)
{
	char *const		builtin_names[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"
	};
	const t_builtin	builtin_funcs[] = {
		run_builtin_echo, run_builtin_cd, run_builtin_pwd, run_builtin_export,
		run_builtin_unset, run_builtin_env, run_builtin_exit
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

// true -> recover
// false -> exit (for builtin exit and executable child failure)

bool	run_raw_command(
	t_vector argv, t_runtime_context *context, t_backup_fds backup
) {
	t_executable	exec;
	t_builtin		builtin_func;

	if (get_builtin(((t_string *)argv.elems)[0].str, &builtin_func))
		return (builtin_func(argv, &context->env, &context->exit_status));
	if (!alloc_executable(&exec, argv, context->env, &context->exit_status))
		return (true);
	if (!run_executable(exec, backup, &context->exit_status))
	{
		free_executable(exec);
		return (false);
	}
	free_executable(exec);
	return (true);
}
