/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 00:34:03 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "utils.h"
#include "expand.h"
#include <fcntl.h>
#include <unistd.h>

t_parsing_status	parse_output_redir(
	t_output_redir *redir, t_tokenizer *tokenizer, t_u8 *exit_status
) {
	t_parsing_status	status;
	t_str				filename;

	status = match_word_token(tokenizer, &filename, NULL, exit_status);
	if (status != PARSING_SUCCEEDED)
	{
		if (status == PARSING_FAILED)
			print_error("output redir: missing filename");
		return (status);
	}
	if (!ft_string_from_str(&redir->filename, filename))
	{
		print_error("output redir: out of memory");
		return (PARSING_CANCELED);
	}
	return (PARSING_SUCCEEDED);
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
