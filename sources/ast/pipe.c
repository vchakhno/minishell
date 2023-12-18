/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 21:38:10 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	alloc_pipe_ast(t_pipe_ast *ast)
{
	if (!ft_vector_alloc(&ast->pipes, sizeof(t_cmd_ast), 8))
		return (false);
	return (true);
}

bool	parse_pipe_ast(
	t_pipe_ast *ast, t_tokenizer *tokenizer, enum e_syntax_error *error
) {
	t_cmd_ast	command;

	while (true)
	{
		if (!alloc_cmd_ast(&command))
		{
			*error = SYNTAX_ERROR_MALLOC;
			return (false);
		}
		if (!parse_cmd_ast(&command, tokenizer, error))
		{
			free_cmd_ast(command);
			return (false);
		}
		if (!ft_vector_push(&ast->pipes, &command))
		{
			free_cmd_ast(command);
			*error = SYNTAX_ERROR_MALLOC;
			return (false);
		}
		if (!match_token(tokenizer, "|", "pipe>", error))
			return (*error == SYNTAX_ERROR_NO_MATCH);
	}
	return (true);
}

bool	execute_pipe_ast(
	t_pipe_ast ast, t_session *session, enum e_exec_error *error
) {
	t_u32	i;

	(void) session;
	i = 0;
	while (i < ast.pipes.size)
	{
		execute_cmd_ast(((t_cmd_ast *)ast.pipes.elems)[i], session, error);
		i++;
	}
	return (true);
}

void	free_pipe_ast(t_pipe_ast ast)
{
	t_u32	i;

	i = 0;
	while (i < ast.pipes.size)
	{
		free_cmd_ast(((t_cmd_ast *)ast.pipes.elems)[i]);
		i++;
	}
	ft_vector_free(ast.pipes);
}
