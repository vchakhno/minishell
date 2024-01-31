/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 11:48:25 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"
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
	t_pipeline pipeline, pid_t *pids, t_runtime_context *context
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
			context->exit_status = 1;
			return (true);
		}
		if (pids[i] == 0)
		{
			if (!apply_pipe(&input, pipe_fds))
				context->exit_status = 1;
			else
				run_simple_command(
					&((t_simple_command *)pipeline.elems)[i], context);
			return (false);
		}
		i++;
	}
	close(input);
	return (true);
}

void	wait_pipeline(t_u32 size, pid_t *pids, t_u8 *exit_status)
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
		*exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		*exit_status = 128 + WTERMSIG(wstatus);
}

// returns recovers

bool	run_pipeline(t_pipeline pipeline, t_runtime_context *context)
{
	pid_t	*pids;

	if (pipeline.size == 1)
		return (run_simple_command(&((t_simple_command *)pipeline.elems)[0],
			context));
	if (!ft_mem_malloc(&pids, pipeline.size * sizeof(pid_t)))
	{
		context->exit_status = 1;
		return (true);
	}
	if (!start_pipeline(pipeline, pids, context))
	{
		free(pids);
		return (false);
	}
	wait_pipeline(pipeline.size, pids, &context->exit_status);
	free(pids);
	return (true);
}
