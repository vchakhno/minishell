/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/21 13:57:53 by vchakhno         ###   ########.fr       */
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
	t_token			token;

	if (!match_redir_op(tokenizer, &redir.type, error)
		|| !peek_token(tokenizer, &token, "redir> ",
			(enum e_prompt_error *)error))
		return (false);
	if (token.type != TOKEN_WORD)
	{
		*error = SYNTAX_ERROR_NO_MATCH;
		return (false);
	}
	consume_token(tokenizer, NULL, NULL);
	if (!ft_string_from_str(&redir.filename, token.content))
	{
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	if (!ft_vector_push(redirs, &redir))
	{
		ft_string_free(redir.filename);
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	return (true);
}

bool	execute_cmd_redir(t_redirection redir, enum e_exec_error *error)
{
	t_i32	fd;

	if (redir.type == REDIR_IN)
	{
		fd = open(redir.filename.c_str, O_RDONLY);
		if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
		{
			*error = EXEC_ERROR_RECOVER;
			return (false);
		}
		close(fd);
	}
	else if (redir.type == REDIR_OUT)
	{
		fd = open(redir.filename.c_str, O_WRONLY | O_CREAT | O_TRUNC);
		if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
		{
			*error = EXEC_ERROR_RECOVER;
			return (false);
		}
		close(fd);
	}
	else if (redir.type == REDIR_APPEND)
	{
		fd = open(redir.filename.c_str, O_WRONLY | O_CREAT | O_APPEND);
		if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
		{
			*error = EXEC_ERROR_RECOVER;
			return (false);
		}
		close(fd);
	}
	return (true);
}

bool	execute_cmd_redirs(t_vector redirs, enum e_exec_error *error)
{
	t_u32	i;

	i = 0;
	while (i < redirs.size)
	{
		if (!execute_cmd_redir(((t_redirection *)redirs.elems)[i], error))
			return (false);
		i++;
	}
	return (true);
}