/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 01:12:40 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "utils.h"
#include "expand.h"
#include <fcntl.h>
#include <unistd.h>

bool	parse_output_redir(
	t_output_redir *redir, t_tokenizer *tokenizer, enum e_parsing_error *error
) {
	t_str	filename;

	if (!match_word_token(tokenizer, &filename, NULL, error))
	{
		if (*error == PARSING_ERROR_SYNTAX)
			print_error("output redir: missing filename");
		return (false);
	}
	if (!ft_string_from_str(&redir->filename, filename))
	{
		print_error("output redir: out of memory");
		*error = PARSING_ERROR_CANCEL;
		return (false);
	}
	return (true);
}

// TODO: add filename expand
// All errors recover

bool	run_output_redir(t_output_redir *redir, t_runtime_context context)
{
	t_i32		fd;
	t_string	filename;

	if (!expand_redir(redir->filename.str, context, &filename))
		return (false);
	fd = open(filename.c_str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1 || !move_fd(fd, STDOUT_FILENO))
	{
		print_error("output redir: invalid file");
		ft_string_free(filename);
		return (false);
	}
	ft_string_free(filename);
	return (true);
}

void	free_output_redir(t_output_redir redir)
{
	ft_string_free(redir.filename);
}
