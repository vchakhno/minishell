/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/11 12:44:52 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_ast_command(
	t_ast_command *ast, t_vector *tokens, t_program *program
) {
	t_token		token;
	t_string	arg;

	if (!ft_vector_alloc(&ast->argv, sizeof(t_string), 10))
		return (false);
	if (!ft_vector_alloc(&ast->redirs, sizeof(t_ast_redirection), 10))
	{
		ft_vector_free(ast->argv);
		return (false);
	}
	if (!peek_token(tokens, &token, program)
		|| token.type != TOKEN_IDENT
		|| !ft_string_from_str(&arg, token.content))
	{
		ft_vector_free(ast->redirs);
		ft_vector_free(ast->argv);
		return (false);
	}
	ft_vector_push(&ast->argv, &arg);
	return (true);
}

bool	parse_ast_pipes(t_ast *ast, t_vector *tokens, t_program *program)
{
	t_ast_command	command;
	bool			matches;

	if (!ft_vector_alloc(&ast->pipes, sizeof(t_ast_command), 8))
		return (false);
	if (!parse_ast_command(&command, tokens, program)
		|| !ft_vector_push(&ast->pipes, &command)
		|| !match_token(tokens, "|", program, &matches))
	{
		ft_vector_free(ast->pipes);
		return (false);
	}
	while (matches)
	{
		if (!parse_ast_command(&command, tokens, program)
			|| !ft_vector_push(&ast->pipes, &command)
			|| !match_token(tokens, "|", program, &matches))
		{
			ft_vector_free(ast->pipes);
			return (false);
		}
	}
	return (true);
}

bool	parse_ast(t_ast *ast, t_program *program)
{
	t_vector	tokens;

	if (!ft_vector_alloc(&tokens, sizeof(t_token), 32))
		return (false);
	if (!parse_ast_pipes(ast, &tokens, program))
	{
		ft_vector_free(tokens);
		return (false);
	}
	ft_vector_free(tokens);
	return (true);
}

bool	execute_ast_command(t_ast_command ast, t_session *session)
{
	(void) session;
	(void) ast;
	ft_println("Cmd: {str}", ((t_string *)ast.argv.elems)[0].str);
	return (true);
}

bool	execute_ast(t_ast ast, t_session *session)
{
	t_u32	i;

	ft_println("Pipe node: ({u32})", ast.pipes.size);
	(void) session;
	i = 0;
	while (i < ast.pipes.size)
	{
		execute_ast_command(
			((t_ast_command *)ast.pipes.elems)[i], session);
		i++;
	}
	return (true);
}

void	free_ast_command(t_ast_command ast)
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

void	free_ast(t_ast ast)
{
	t_u32	i;

	i = 0;
	while (i < ast.pipes.size)
	{
		free_ast_command(((t_ast_command *)ast.pipes.elems)[i]);
		i++;
	}
	ft_vector_free(ast.pipes);
}