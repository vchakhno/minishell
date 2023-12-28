/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:41:47 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/28 20:09:46 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <wait.h>

bool	store_heredoc(
	t_heredoc *heredoc, t_lines *lines, enum e_prompt_error *error
) {
	t_str	line;

	if (!ft_string_alloc(&heredoc->content, 30))
	{
		*error = PROMPT_ERROR_MALLOC;
		return (false);
	}
	line = ft_str("");
	while (line.len - 1 != heredoc->delimiter.len
		|| !ft_mem_equal(line.c_str, heredoc->delimiter.c_str, line.len - 1))
	{
		if (!ft_string_append_str(&heredoc->content, line))
		{
			*error = PROMPT_ERROR_MALLOC;
			return (false);
		}
		if (!read_line(lines, &line, "heredoc> ", error))
			return (false);
	}
	return (true);
}

bool	start_heredoc(t_heredoc heredoc, enum e_exec_error *error)
{
	int	pipe_fds[2];

	pipe(pipe_fds);
	if (!ft_fork(&heredoc.pid))
	{
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
	if (heredoc.pid == 0)
	{
		close(pipe_fds[0]);
		move_fd(pipe_fds[1], STDOUT_FILENO);
		ft_printf("{str}", heredoc.content.str);
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
	move_fd(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[1]);
	return (true);
}

void	free_heredoc(t_heredoc heredoc)
{
	ft_string_free(heredoc.content);
}
