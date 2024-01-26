/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/26 09:07:25 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <unistd.h>
#include <wait.h>

bool	next_pipe(int *input, int pipe_fds[2], bool first, bool last)
{
	if (first)
		*input = STDIN_FILENO;
	else
	{
		if (pipe_fds[1] != STDOUT_FILENO)
			close(pipe_fds[1]);
		if (*input != STDIN_FILENO)
			close(*input);
		*input = pipe_fds[0];
	}
	if (!last)
		return (pipe(pipe_fds) == 0);
	else
	{
		pipe_fds[1] = STDOUT_FILENO;
		pipe_fds[0] = STDIN_FILENO;
	}
	return (true);
}

bool	apply_pipe(int *input, int pipe_fds[2])
{
	if (pipe_fds[0] != STDIN_FILENO)
		close(pipe_fds[0]);
	return (
		move_fd(*input, STDIN_FILENO)
		& (int) move_fd(pipe_fds[1], STDOUT_FILENO)
	);
}
