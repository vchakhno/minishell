/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/17 23:07:37 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	alloc_command_ast(t_command_ast *ast)
{
	if (!ft_vector_alloc(&ast->argv, sizeof(t_string), 10))
		return (false);
	if (!ft_vector_alloc(&ast->redirs, sizeof(t_ast_redirection), 10))
	{
		ft_vector_free(ast->argv);
		return (false);
	}
	return (true);
}

bool	parse_command_ast(
	t_command_ast *ast, t_tokenizer *tokenizer, enum e_syntax_error *error
) {
	t_token		token;
	t_string	arg;

	if (!peek_token(tokenizer, &token, "cmd> ", (enum e_prompt_error *)error))
		return (false);
	if (token.type != TOKEN_WORD)
	{
		*error = SYNTAX_ERROR_NO_MATCH;
		return (false);
	}
	consume_token(tokenizer, "cmd> ", (enum e_prompt_error *)error);
	if (!ft_string_from_str(&arg, token.content))
	{
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	ft_vector_push(&ast->argv, &arg);
	return (true);
}

bool	execute_command_ast(t_command_ast ast, t_session *session)
{
	(void) session;
	ft_println("Cmd: {str}", ((t_string *)ast.argv.elems)[0].str);
	return (true);
}

void	free_command_ast(t_command_ast ast)
{
	t_u32	i;

	i = 0;
	while (i < ast.argv.size)
	{
		ft_string_free(((t_string *)ast.argv.elems)[i]);
		i++;
	}
	ft_vector_free(ast.argv);
	i = 0;
	while (i < ast.redirs.size)
	{
		ft_string_free(
			((t_ast_redirection *)ast.redirs.elems)[i].filename);
		i++;
	}
	ft_vector_free(ast.redirs);
}
