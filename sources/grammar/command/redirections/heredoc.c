/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:41:47 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 03:57:04 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "utils.h"
#include <unistd.h>
#include <wait.h>
#include <signal.h>

// TODO: add body expansion (in run heredoc)

t_parsing_status	parse_heredoc_body(
	t_heredoc *heredoc, t_shell_input *input, t_u8 *exit_status
) {
	t_parsing_status	status;
	t_str				line;

	line = ft_str("");
	while (line.len - 1 != heredoc->delimiter.len
		|| !ft_mem_equal(line.c_str, heredoc->delimiter.c_str, line.len - 1))
	{
		if (!ft_string_append_str(&heredoc->body, line))
		{
			print_error("heredoc: out of memory");
			return (PARSING_CANCELED);
		}
		status = (t_parsing_status) read_line(input, &line, "heredoc> ",
				exit_status);
		if (status == PARSING_EXITED)
		{
			print_error("heredoc: warning: heredoc delimited by end-of-file");
			break ;
		}
		if (status != PARSING_SUCCEEDED)
			return (PARSING_CANCELED);
	}
	return (PARSING_SUCCEEDED);
}

t_parsing_status	parse_heredoc_delimiter(
	t_heredoc *heredoc, t_tokenizer *tokenizer, t_u8 *exit_status
) {
	t_parsing_status	status;
	t_str				delimiter;

	status = match_word_token(tokenizer, &delimiter, NULL, exit_status);
	if (status != PARSING_SUCCEEDED)
	{
		if (status == PARSING_FAILED)
			print_error("heredoc: missing delimiter");
		return (status);
	}
	if (!ft_string_from_str(&heredoc->delimiter, delimiter))
	{
		print_error("heredoc: out of memory");
		return (PARSING_CANCELED);
	}
	return (PARSING_SUCCEEDED);
}

// TODO: add delimiter checking and unquoting

t_parsing_status	parse_heredoc(
	t_heredoc *heredoc, t_tokenizer *tokenizer, t_u8 *exit_status
) {
	t_parsing_status	status;

	status = parse_heredoc_delimiter(heredoc, tokenizer, exit_status);
	if (status != PARSING_SUCCEEDED)
		return (status);
	if (!ft_string_alloc(&heredoc->body, 128))
	{
		print_error("heredoc: out of memory");
		ft_string_free(heredoc->delimiter);
		return (PARSING_CANCELED);
	}
	status = parse_heredoc_body(heredoc, tokenizer->input, exit_status);
	if (status != PARSING_SUCCEEDED)
	{
		ft_string_free(heredoc->body);
		ft_string_free(heredoc->delimiter);
		return (status);
	}
	return (PARSING_SUCCEEDED);
}

void	free_heredoc(t_heredoc heredoc)
{
	ft_string_free(heredoc.body);
	ft_string_free(heredoc.delimiter);
}
