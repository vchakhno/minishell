/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 05:51:46 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

bool	alloc_ast(t_ast_root *ast)
{
	return (alloc_pipeline(&ast->pipes));
}

t_parsing_status	parse_ast(t_ast_root *ast, t_shell_input *input)
{
	t_parsing_status	status;
	t_tokenizer			tokenizer;

	if (!alloc_tokenizer(&tokenizer, input))
		return (false);
	status = parse_pipeline(&ast->pipes, &tokenizer);
	free_tokenizer(tokenizer);
	return (status);
}

bool	run_ast(t_ast_root ast, t_runtime_context *context)
{
	return (run_pipeline(ast.pipes, context));
}

void	free_ast(t_ast_root ast)
{
	free_pipeline(ast.pipes);
}
