/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:23:46 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/21 15:13:11 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	execute_command_sync(
	t_vector argv, t_session *session, t_backup_fds backup,
	enum e_exec_error *error
) {
	t_executable	exec;

	if (!alloc_executable(&exec, argv, session->env, error))
		return (false);
	if (!run_executable_sync(exec, backup, error))
	{
		free_executable(exec);
		return (false);
	}
	free_executable(exec);
	return (true);
}

bool	execute_command_async(
	t_vector argv, t_session *session, enum e_exec_error *error
) {
	t_executable	exec;

	if (!alloc_executable(&exec, argv, session->env, error))
		return (false);
	run_executable_async(exec);
	free_executable(exec);
	*error = EXEC_ERROR_EXIT;
	return (false);
}
