/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:41:47 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/29 07:52:58 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <wait.h>
#include <signal.h>

// TODO: add body expansion

bool	parse_heredoc_body(
	t_heredoc *heredoc, t_lines *lines, enum e_prompt_error *error
) {
	t_str	line;

	if (!ft_string_alloc(&heredoc->body, 128))
	{
		print_error("heredoc body: out of memory");
		*error = PROMPT_ERROR_MALLOC;
		return (false);
	}
	line = ft_str("");
	while (line.len - 1 != heredoc->delimiter.len
		|| !ft_mem_equal(line.c_str, heredoc->delimiter.c_str, line.len - 1))
	{
		if (!ft_string_append_str(&heredoc->body, line))
		{
			ft_string_free(heredoc->body);
			print_error("heredoc body: out of memory");
			*error = PROMPT_ERROR_MALLOC;
			return (false);
		}
		if (!read_line(lines, &line, "heredoc> ", error))
		{
			if (*error == PROMPT_ERROR_CTRL_C)
				print_error("heredoc: warning: "
					"heredoc delimited by end-of-file");
			ft_string_free(heredoc->body);
			return (false);
		}
	}
	return (true);
}

// TODO: add delimiter checking and unquoting

bool	parse_heredoc(
	t_heredoc *heredoc, t_tokenizer *tokenizer, enum e_syntax_error *error
) {
	t_str	delimiter;

	if (!match_word_token(tokenizer, &delimiter, NULL, error))
	{
		if (*error == SYNTAX_ERROR_NO_MATCH)
			print_error("heredoc: missing delimiter");
		return (false);
	}
	if (!ft_string_from_str(&heredoc->delimiter, delimiter))
	{
		print_error("heredoc: out of memory");
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	if (!parse_heredoc_body(heredoc, tokenizer->lines,
			(enum e_prompt_error *)error))
	{
		ft_string_free(heredoc->delimiter);
		return (false);
	}
	return (true);
}

bool	run_heredoc(t_heredoc *heredoc, enum e_exec_error *error)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
	{
		print_error("heredoc: out of file descriptors");
		*error = EXEC_ERROR_RECOVER;
		return (false);
	}
	if (!ft_fork(&heredoc->pid))
	{
		print_error("heredoc: cannot fork");
		*error = EXEC_ERROR_RECOVER;
		return (false);
	}
	if (heredoc->pid == 0)
	{
		close(pipe_fds[0]);
		if (!move_fd(pipe_fds[1], STDOUT_FILENO))
		{
			print_error("heredoc: out of file descriptors");
			*error = EXEC_ERROR_EXIT;
			return (false);
		}
		ft_printf("{str}", heredoc->body.str);
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
	close(pipe_fds[1]);
	if (!move_fd(pipe_fds[0], STDIN_FILENO))
	{
		print_error("heredoc: out of file descriptors");
		*error = EXEC_ERROR_RECOVER;
		return (false);
	}
	return (true);
}

void	cleanup_heredoc(t_heredoc heredoc)
{
	ft_eprintln("Killing pid {u32}", heredoc.pid);
	kill(heredoc.pid, SIGKILL);
	waitpid(heredoc.pid, NULL, 0);
}

void	free_heredoc(t_heredoc heredoc)
{
	ft_string_free(heredoc.body);
	ft_string_free(heredoc.delimiter);
}
