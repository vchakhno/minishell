/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/31 18:39:37 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include <fcntl.h>
#include <unistd.h>

t_parsing_status	match_redir_op(
	t_tokenizer *tokenizer, enum e_redir_type *type
) {
	t_parsing_status	status;
	char *const			redir_ops[] = {"<", ">", "<<", ">>"};
	t_u32				i;

	i = 0;
	while (i < (t_u32) sizeof redir_ops / sizeof * redir_ops)
	{
		status = match_token(tokenizer, redir_ops[i], NULL);
		if (status == PARSING_SUCCEEDED)
		{
			*type = i;
			return (PARSING_SUCCEEDED);
		}
		if (status == PARSING_CANCELED || status == PARSING_EXITED)
			return (status);
		i++;
	}
	return (PARSING_FAILED);
}

t_parsing_status	parse_redirection(
	t_redirection *redir, t_tokenizer *tokenizer
) {
	if (redir->type == REDIR_INPUT)
		return (parse_input_redir(&redir->input, tokenizer));
	if (redir->type == REDIR_OUTPUT)
		return (parse_output_redir(&redir->output, tokenizer));
	if (redir->type == REDIR_APPEND)
		return (parse_append_redir(&redir->append, tokenizer));
	if (redir->type == REDIR_HEREDOC)
		return (parse_heredoc(&redir->heredoc, tokenizer));
	return (PARSING_CANCELED);
}

bool	run_redirection(
	t_redirection *redir, bool *recovers, t_runtime_context context
) {
	*recovers = true;
	if (redir->type == REDIR_INPUT)
		return (run_input_redir(&redir->input, context));
	if (redir->type == REDIR_OUTPUT)
		return (run_output_redir(&redir->output, context));
	if (redir->type == REDIR_APPEND)
		return (run_append_redir(&redir->append, context));
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
