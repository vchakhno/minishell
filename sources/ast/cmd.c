/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/22 18:23:46 by vchakhno         ###   ########.fr       */
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

// For when pipe has a single child
// 
// In this case, executables fork (and builtins don't)
// Then both are supposed to return normally
// /!\ There can also be 2 returns in case execve fails

bool	run_cmd_ast(
	t_cmd_ast ast, t_session *session, enum e_exec_error *error
) {
	t_backup_fds	backup;
	bool			status;

	if (!save_backup_fds(&backup))
	{
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
	status = (run_cmd_redirs(ast.redirs, error)
			&& run_command(ast.argv, session, backup, error));
	if (!restore_backup_fds(backup))
	{
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
	ft_oprintln(ft_stderr(), "Status: {u8}", session->last_status);
	return (status);
}

// For when pipe has multiple children
//
// In this case, executables don't fork (nor do builtins)
// Executables are not supposed to return, except if execve fails

void	start_cmd_ast(
	t_cmd_ast ast, t_session *session, enum e_exec_error *error
) {
	if (!run_cmd_redirs(ast.redirs, error))
		return ;
	start_command(ast.argv, session, error);
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
