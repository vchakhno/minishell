/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/21 13:45:10 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

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
	t_vector *argv, t_tokenizer *tokenizer, enum e_syntax_error *error
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
	if (!ft_vector_push(argv, &arg))
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
		if (parse_cmd_arg(&ast->argv, tokenizer, error))
			continue ;
		if (*error != SYNTAX_ERROR_NO_MATCH)
			return (false);
		if (parse_cmd_redir(&ast->redirs, tokenizer, error))
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
	t_backup_fds	backup;

	if (!save_backup_fds(&backup))
	{
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
	if (!execute_cmd_redirs(ast.redirs, error)
		|| !execute_command(ast.argv, session, error))
	{
		if (!restore_backup_fds(backup) && *error == EXEC_ERROR_RECOVER)
			*error = EXEC_ERROR_EXIT;
		return (false);
	}
	if (!restore_backup_fds(backup))
	{
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
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
