/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 17:34:15 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_cmd_ast *ast, t_tokenizer *tokenizer, enum e_syntax_error *error
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
	if (!ft_vector_push(&ast->redirs, &redir))
	{
		ft_string_free(redir.filename);
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	return (true);
}
