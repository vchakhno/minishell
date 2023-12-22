/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:23:46 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/22 18:23:46 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	run_command(
	t_vector argv, t_session *session, t_backup_fds backup,
	enum e_exec_error *error
) {
	t_executable	exec;

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

bool	start_command(
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
