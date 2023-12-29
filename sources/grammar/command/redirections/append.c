/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/29 05:33:45 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

bool	parse_append_redir(
	t_append_redir *redir, t_tokenizer *tokenizer, enum e_syntax_error *error
) {
	t_str	filename;

	if (!match_word_token(tokenizer, &filename, NULL, error))
	{
		if (*error == SYNTAX_ERROR_NO_MATCH)
			print_error("append redir: missing filename");
		return (false);
	}
	if (!ft_string_from_str(&redir->filename, filename))
	{
		print_error("append redir: out of memory");
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	return (true);
}

// TODO: add filename expand
// All errors recover

bool	run_append_redir(t_append_redir *redir)
{
	t_i32	fd;

	fd = open(redir->filename.c_str, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1 || !move_fd(fd, STDOUT_FILENO))
	{
		print_error("append redir: invalid file");
		return (false);
	}
	return (true);
}

void	free_append_redir(t_append_redir redir)
{
	ft_string_free(redir.filename);
}
