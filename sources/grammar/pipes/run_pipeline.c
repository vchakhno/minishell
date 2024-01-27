/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 00:27:00 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

void	cleanup_pipeline(t_u32 size, pid_t *pids)
{
	t_u32	i;

	i = 0;
	while (i < size)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i < size)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
}

// if a next_pipe fails at some point, kill the previous processes
// inside the fork:
// if a redirection (apply_pipe) fails, don't execute the command
// and set exit_status to 1
// if the command fails with exit (exit builtin, or execve failure), ignore it
// (DO NOT CLEANUP PREVIOUS COMMANDS, exit should be ignored)

// returns recovers

bool	start_pipeline(
	t_vector pipeline, pid_t *pids, t_session *session
) {
	t_u32	i;
	int		input;
	int		pipe_fds[2];

	i = 0;
	while (i < pipeline.size)
	{
		if (!next_pipe(&input, pipe_fds, i == 0, i == pipeline.size - 1)
			|| !ft_fork(&pids[i]))
		{
			cleanup_pipeline(i, pids);
			session->exit_status = 1;
			return (true);
		}
		if (pids[i] == 0)
		{
			if (!apply_pipe(&input, pipe_fds))
				session->exit_status = 1;
			else
				run_simple_command(
					&((t_simple_command *)pipeline.elems)[i],
					&session->env, &session->exit_status);
			return (false);
		}
		i++;
	}
	close(input);
	return (true);
}

void	wait_pipeline(t_u32 size, pid_t *pids, t_session *session)
{
	t_u32	i;
	int		wstatus;

	i = 0;
	while (i < size)
	{
		waitpid(pids[i], &wstatus, 0);
		i++;
	}
	if (WIFEXITED(wstatus))
		session->exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		session->exit_status = 128 + WTERMSIG(wstatus);
}

// returns recovers

bool	run_pipeline(t_vector pipeline, t_session *session)
{
	pid_t	*pids;

	if (pipeline.size == 1)
		return (run_simple_command(&((t_simple_command *)pipeline.elems)[0],
			&session->env, &session->exit_status));
	if (!ft_mem_malloc(&pids, pipeline.size * sizeof(pid_t)))
	{
		session->exit_status = 1;
		return (true);
	}
	if (!start_pipeline(pipeline, pids, session))
	{
		free(pids);
		return (false);
	}
	wait_pipeline(pipeline.size, pids, session);
	free(pids);
	ft_eprintln("[DEBUG] Pipeline status: {u8}", session->exit_status);
	return (true);
}
