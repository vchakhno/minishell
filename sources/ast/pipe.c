/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 14:43:01 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	alloc_pipe_ast(t_pipe_ast *ast)
{
	if (!ft_vector_alloc(&ast->pipes, sizeof(t_command_ast), 8))
		return (false);
	return (true);
}

bool	parse_pipe_ast(
	t_pipe_ast *ast, t_tokenizer *tokenizer, enum e_syntax_error *error
) {
	t_command_ast	command;

	while (true)
	{
		if (!alloc_command_ast(&command))
		{
			*error = SYNTAX_ERROR_MALLOC;
			return (false);
		}
		if (!parse_command_ast(&command, tokenizer, error))
		{
			free_command_ast(command);
			return (false);
		}
		if (!ft_vector_push(&ast->pipes, &command))
		{
			free_command_ast(command);
			*error = SYNTAX_ERROR_MALLOC;
			return (false);
		}
		if (!match_token(tokenizer, "|", "pipe>", error))
			return (*error == SYNTAX_ERROR_NO_MATCH);
	}
	return (true);
}

bool	execute_pipe_ast(t_pipe_ast ast, t_session *session)
{
	t_u32	i;

	// ft_println("Pipe node: ({u32})", ast.pipes.size);
	(void) session;
	i = 0;
	while (i < ast.pipes.size)
	{
		execute_command_ast(((t_command_ast *)ast.pipes.elems)[i], session);
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
		free_command_ast(((t_command_ast *)ast.pipes.elems)[i]);
		i++;
	}
	ft_vector_free(ast.pipes);
}
