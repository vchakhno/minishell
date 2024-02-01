/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:41:47 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 01:39:49 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "utils.h"
#include <unistd.h>
#include <wait.h>
#include <signal.h>

bool	start_heredoc(int pipe_fds[2], t_heredoc *heredoc, bool *recovers)
{
	close(pipe_fds[0]);
	if (!move_fd(pipe_fds[1], STDOUT_FILENO))
		print_error("heredoc: out of file descriptors");
	else
		ft_printf("{str}", heredoc->body.str);
	*recovers = false;
	return (false);
}

bool	run_heredoc(t_heredoc *heredoc, bool *recovers)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
	{
		print_error("heredoc: out of file descriptors");
		*recovers = true;
		return (false);
	}
	if (!ft_fork(&heredoc->pid))
	{
		print_error("heredoc: cannot fork");
		*recovers = true;
		return (false);
	}
	if (heredoc->pid == 0)
		return (start_heredoc(pipe_fds, heredoc, recovers));
	close(pipe_fds[1]);
	if (!move_fd(pipe_fds[0], STDIN_FILENO))
	{
		print_error("heredoc: out of file descriptors");
		*recovers = true;
		return (false);
	}
	return (true);
}

void	cleanup_heredoc(t_heredoc heredoc)
{
	kill(heredoc.pid, SIGKILL);
	waitpid(heredoc.pid, NULL, 0);
}
