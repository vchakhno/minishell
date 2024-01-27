/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 00:15:21 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include <fcntl.h>
#include <unistd.h>

bool	match_redir_op(
	t_tokenizer *tokenizer, enum e_redir_type *type, enum e_parsing_error *error
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
	*error = PARSING_ERROR_SYNTAX;
	return (false);
}

bool	parse_redirection(
	t_redirection *redir, t_tokenizer *tokenizer, enum e_parsing_error *error
) {

	if (!match_redir_op(tokenizer, &redir->type, error))
		return (false);
	return (
		(redir->type == REDIR_INPUT
			&& parse_input_redir(&redir->input, tokenizer, error))
		|| (redir->type == REDIR_OUTPUT
			&& parse_output_redir(&redir->output, tokenizer, error))
		|| (redir->type == REDIR_APPEND
			&& parse_append_redir(&redir->append, tokenizer, error))
		|| (redir->type == REDIR_HEREDOC
			&& parse_heredoc(&redir->heredoc, tokenizer, error))
	);
}

bool	run_redirection(
	t_redirection *redir, bool *recovers, t_env env, t_u8 exit_status
) {
	*recovers = true;
	if (redir->type == REDIR_INPUT)
		return (run_input_redir(&redir->input, env, exit_status));
	if (redir->type == REDIR_OUTPUT)
		return (run_output_redir(&redir->output, env, exit_status));
	if (redir->type == REDIR_APPEND)
		return (run_append_redir(&redir->append, env, exit_status));
	if (redir->type == REDIR_HEREDOC)
		return (run_heredoc(&redir->heredoc, recovers));
	return (false);
}

void	cleanup_redirection(t_redirection redir)
{
	if (redir.type == REDIR_HEREDOC)
		cleanup_heredoc(redir.heredoc);
}

void	free_redirection(t_redirection redir)
{
	if (redir.type == REDIR_INPUT)
		free_input_redir(redir.input);
	else if (redir.type == REDIR_OUTPUT)
		free_output_redir(redir.output);
	else if (redir.type == REDIR_APPEND)
		free_append_redir(redir.append);
	else if (redir.type == REDIR_HEREDOC)
		free_heredoc(redir.heredoc);
}
