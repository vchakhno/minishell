/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 21:41:16 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	alloc_ast(t_ast_root *ast)
{
	return (alloc_pipe_ast(&ast->pipes));
}

bool	parse_ast(
	t_ast_root *ast, t_lines *lines, enum e_syntax_error *error)
{
	t_tokenizer	tokenizer;

	if (!alloc_tokenizer(&tokenizer, lines))
		return (false);
	if (!parse_pipe_ast(&ast->pipes, &tokenizer, error))
	{
		free_tokenizer(tokenizer);
		return (false);
	}
	free_tokenizer(tokenizer);
	return (true);
}

bool	execute_ast(
	t_ast_root ast, t_session *session, enum e_exec_error *error
) {
	return (execute_pipe_ast(ast.pipes, session, error));
}

void	free_ast(t_ast_root ast)
{
	free_pipe_ast(ast.pipes);
}
