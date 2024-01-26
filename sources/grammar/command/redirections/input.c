/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/26 02:59:05 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

bool	parse_input_redir(
	t_input_redir *redir, t_tokenizer *tokenizer, enum e_parsing_error *error
) {
	t_str	filename;

	if (!match_word_token(tokenizer, &filename, NULL, error))
	{
		if (*error == PARSING_ERROR_SYNTAX)
			print_error("input redir: missing filename");
		return (false);
	}
	if (!ft_string_from_str(&redir->filename, filename))
	{
		print_error("input redir: out of memory");
		*error = PARSING_ERROR_CANCEL;
		return (false);
	}
	return (true);
}

// TODO: add filename expand
// All errors recover

bool	run_input_redir(t_input_redir *redir)
{
	t_i32	fd;

	fd = open(redir->filename.c_str, O_RDONLY, 0666);
	if (fd == -1 || !move_fd(fd, STDOUT_FILENO))
	{
		print_error("input redir: invalid file");
		return (false);
	}
	return (true);
}

void	free_input_redir(t_input_redir redir)
{
	ft_string_free(redir.filename);
}
