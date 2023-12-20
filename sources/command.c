/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:23:46 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/20 01:36:07 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	execute_command(
	t_vector argv, t_session *session, enum e_exec_error *error
) {
	t_executable	exec;

	if (!alloc_executable(&exec, argv, session->env, error))
		return (false);
	if (!run_executable(exec, error))
	{
		free_executable(exec);
		return (false);
	}
	free_executable(exec);
	return (true);
}
