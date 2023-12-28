/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:41:47 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/28 17:20:26 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	store_heredoc(
	t_redirection *heredoc, t_lines *lines, enum e_prompt_error *error
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

void	run_heredoc(t_redirection heredoc)
{
	ft_println("-- Heredoc --");
	ft_println("{str}", heredoc.content.str);
	ft_println("-- End of heredoc --");
}

void	free_heredoc(t_redirection heredoc)
{
	ft_string_free(heredoc.content);
}
