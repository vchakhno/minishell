/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 21:37:44 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	alloc_cmd_ast(t_cmd_ast *ast)
{
	if (!ft_vector_alloc(&ast->argv, sizeof(t_string), 10))
		return (false);
	if (!ft_vector_alloc(&ast->redirs, sizeof(t_redirection), 10))
	{
		ft_vector_free(ast->argv);
		return (false);
	}
	return (true);
}

bool	parse_cmd_arg(
	t_cmd_ast *ast, t_tokenizer *tokenizer, enum e_syntax_error *error
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
	consume_token(tokenizer, NULL, NULL);
	if (!ft_string_from_str(&arg, token.content))
	{
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	if (!ft_vector_push(&ast->argv, &arg))
	{
		ft_string_free(arg);
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	return (true);
}

bool	parse_cmd_ast(
	t_cmd_ast *ast, t_tokenizer *tokenizer, enum e_syntax_error *error
) {
	while (true)
	{
		if (parse_cmd_arg(ast, tokenizer, error))
			continue ;
		if (*error != SYNTAX_ERROR_NO_MATCH)
			return (false);
		if (parse_cmd_redir(ast, tokenizer, error))
			continue ;
		if (*error != SYNTAX_ERROR_NO_MATCH)
			return (false);
		break ;
	}
	return (ast->argv.size);
}

bool	execute_cmd_ast(
	t_cmd_ast ast, t_session *session, enum e_exec_error *error
) {
	t_executable	exec;

	if (!alloc_executable(&exec, ast.argv, session->env, error))
		return (false);
	if (!run_executable(exec, error))
	{
		free_executable(exec);
		return (false);
	}
	free_executable(exec);
	return (true);
}

void	free_cmd_ast(t_cmd_ast ast)
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
			((t_redirection *)ast.redirs.elems)[i].filename);
		i++;
	}
	ft_vector_free(ast.redirs);
}
