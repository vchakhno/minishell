/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/28 20:09:24 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

bool	match_redir_op(
	t_tokenizer *tokenizer, enum e_redir_type *type, enum e_syntax_error *error
) {
	char *const		redir_ops[] = {"<", ">", "<<", ">>"};
	t_u32			i;

	i = 0;
	while (i < (t_u32) sizeof redir_ops / sizeof * redir_ops)
	{
		if (match_token(tokenizer, redir_ops[i], NULL, error))
		{
			*type = i;
			return (true);
		}
		i++;
	}
	*error = SYNTAX_ERROR_NO_MATCH;
	return (false);
}

bool	parse_cmd_redir(
	t_vector *redirs, t_tokenizer *tokenizer, enum e_syntax_error *error
) {
	t_redirection	redir;
	t_str			filename;

	if (!match_redir_op(tokenizer, &redir.type, error)
		|| !match_word_token(tokenizer, &filename, NULL, error))
		return (false);
	if (!ft_string_from_str(&redir.filename, filename))
	{
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	if (redir.type == REDIR_HEREDOC && !store_heredoc(
			&redir.heredoc, tokenizer->lines, (enum e_prompt_error *)error))
		return (false);
	if (!ft_vector_push(redirs, &redir))
	{
		free_cmd_redir(redir);
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	return (true);
}

bool	run_cmd_redir(t_redirection redir, enum e_exec_error *error)
{
	t_i32	fd;

	if (redir.type == REDIR_HEREDOC)
	{
		if (!start_heredoc(redir.heredoc, error))
			return (false);
		return (true);
	}
	if (redir.type == REDIR_IN)
	{
		fd = open(redir.filename.c_str, O_RDONLY);
		if (fd == -1 || !move_fd(fd, STDIN_FILENO))
		{
			*error = EXEC_ERROR_RECOVER;
			return (false);
		}
	}
	else if (redir.type == REDIR_OUT || redir.type == REDIR_APPEND)
	{
		fd = open(redir.filename.c_str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1 || !move_fd(fd, STDOUT_FILENO))
		{
			*error = EXEC_ERROR_RECOVER;
			return (false);
		}
	}
	else if (redir.type == REDIR_APPEND)
	{
		fd = open(redir.filename.c_str, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1 || !move_fd(fd, STDOUT_FILENO))
		{
			*error = EXEC_ERROR_RECOVER;
			return (false);
		}
	}
	return (true);
}

bool	run_cmd_redirs(t_vector redirs, enum e_exec_error *error)
{
	t_u32	i;

	i = 0;
	while (i < redirs.size)
	{
		if (!run_cmd_redir(((t_redirection *)redirs.elems)[i], error))
			return (false);
		i++;
	}
	return (true);
}

void	free_cmd_redir(t_redirection redir)
{
	if (redir.type == REDIR_HEREDOC)
		free_heredoc(redir.heredoc);
	ft_string_free(redir.filename);
}
