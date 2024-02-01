/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 03:59:26 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "utils.h"
#include "expand.h"
#include <fcntl.h>
#include <unistd.h>

t_parsing_status	parse_input_redir(
	t_input_redir *redir, t_tokenizer *tokenizer, t_u8 *exit_status
) {
	t_parsing_status	status;
	t_str				filename;

	status = match_word_token(tokenizer, &filename, NULL, exit_status);
	if (status != PARSING_SUCCEEDED)
	{
		if (status == PARSING_FAILED)
			print_error("input redir: missing filename");
		return (status);
	}
	if (!ft_string_from_str(&redir->filename, filename))
	{
		print_error("input redir: out of memory");
		return (PARSING_CANCELED);
	}
	return (PARSING_SUCCEEDED);
}

bool	run_input_redir(t_input_redir *redir, t_runtime_context context)
{
	bool		exists;
	t_i32		fd;
	t_string	filename;

	if (!expand_redir(redir->filename.str, context, &filename, &exists))
	{
		print_error("append redir: out of memory");
		return (false);
	}
	if (!exists)
	{
		print_error("append redir: ambiguous redirect");
		return (false);
	}
	fd = open(filename.c_str, O_RDONLY, 0666);
	if (fd == -1 || !move_fd(fd, STDOUT_FILENO))
	{
		print_error("input redir: invalid file");
		ft_string_free(filename);
		return (false);
	}
	ft_string_free(filename);
	return (true);
}

void	free_input_redir(t_input_redir redir)
{
	ft_string_free(redir.filename);
}
