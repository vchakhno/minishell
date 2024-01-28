/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:41:47 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 00:56:19 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "utils.h"
#include <unistd.h>
#include <wait.h>
#include <signal.h>

// TODO: add body expansion

bool	parse_heredoc_body(
	t_heredoc *heredoc, t_shell_input *input, enum e_prompt_error *error
) {
	t_str	line;

	if (!ft_string_alloc(&heredoc->body, 128))
	{
		print_error("heredoc body: out of memory");
		*error = PROMPT_ERROR_CANCEL;
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
			*error = PROMPT_ERROR_CANCEL;
			return (false);
		}
		if (!read_line(input, &line, "heredoc> ", error))
		{
			if (*error == PROMPT_ERROR_CANCEL)
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
	t_heredoc *heredoc, t_tokenizer *tokenizer, enum e_parsing_error *error
) {
	t_str	delimiter;

	if (!match_word_token(tokenizer, &delimiter, NULL, error))
	{
		if (*error == PARSING_ERROR_SYNTAX)
			print_error("heredoc: missing delimiter");
		return (false);
	}
	if (!ft_string_from_str(&heredoc->delimiter, delimiter))
	{
		print_error("heredoc: out of memory");
		*error = PARSING_ERROR_CANCEL;
		return (false);
	}
	if (!parse_heredoc_body(heredoc, tokenizer->input,
			(enum e_prompt_error *)error))
	{
		ft_string_free(heredoc->delimiter);
		return (false);
	}
	return (true);
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
	{
		close(pipe_fds[0]);
		if (!move_fd(pipe_fds[1], STDOUT_FILENO))
			print_error("heredoc: out of file descriptors");
		else
			ft_printf("{str}", heredoc->body.str);
		*recovers = false;
		return (false);
	}
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

void	free_heredoc(t_heredoc heredoc)
{
	ft_string_free(heredoc.body);
	ft_string_free(heredoc.delimiter);
}
