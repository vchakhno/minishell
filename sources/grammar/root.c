/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 08:35:52 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"
#include "prompts.h"

bool	alloc_ast(t_ast_root *ast)
{
	return (alloc_pipeline(&ast->pipes));
}

t_parsing_status	parse_program(t_ast_root *ast, t_tokenizer *tokenizer)
{
	t_parsing_status	status;

	status = match_token(tokenizer, "\n", MAIN_PROMPT);
	if (status == PARSING_SUCCEEDED)
		return (PARSING_CANCELED);
	if (status == PARSING_CANCELED || status == PARSING_EXITED)
		return (status);
	status = parse_pipeline(&ast->pipes, tokenizer);
	if (status != PARSING_SUCCEEDED)
		return (status);
	return (match_token(tokenizer, "\n", NULL));
}

t_parsing_status	parse_ast(t_ast_root *ast, t_shell_input *input)
{
	t_parsing_status	status;
	t_tokenizer			tokenizer;

	if (!alloc_tokenizer(&tokenizer, input))
		return (false);
	status = parse_program(ast, &tokenizer);
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
