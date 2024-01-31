/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 00:20:37 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"
#include "prompts.h"

bool	alloc_ast(t_ast_root *ast)
{
	return (alloc_and_or(&ast->and_or));
}

t_parsing_status	parse_program(
	t_ast_root *ast, t_tokenizer *tokenizer, t_u8 *exit_status
) {
	t_parsing_status	status;

	status = match_token(tokenizer, "\n", MAIN_PROMPT, exit_status);
	if (status == PARSING_SUCCEEDED)
		return (PARSING_CANCELED);
	if (status == PARSING_CANCELED || status == PARSING_EXITED)
		return (status);
	status = parse_and_or(&ast->and_or, tokenizer, exit_status);
	if (status != PARSING_SUCCEEDED)
		return (status);
	return (match_token(tokenizer, "\n", NULL, exit_status));
}

t_parsing_status	parse_ast(
	t_ast_root *ast, t_shell_input *input, t_u8 *exit_status
) {
	t_parsing_status	status;
	t_tokenizer			tokenizer;

	if (!alloc_tokenizer(&tokenizer, input))
		return (false);
	status = parse_program(ast, &tokenizer, exit_status);
	free_tokenizer(tokenizer);
	return (status);
}

bool	run_ast(t_ast_root ast, t_runtime_context *context)
{
	return (run_and_or(ast.and_or, context));
}

void	free_ast(t_ast_root ast)
{
	free_and_or(ast.and_or);
}
