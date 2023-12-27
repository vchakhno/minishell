/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/27 10:04:24 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

bool	alloc_simple_command(t_simple_command *cmd)
{
	if (!ft_vector_alloc(&cmd->argv, sizeof(t_string), 10))
		return (false);
	if (!ft_vector_alloc(&cmd->redirs, sizeof(t_redirection), 10))
	{
		ft_vector_free(cmd->argv);
		return (false);
	}
	return (true);
}

bool	parse_simple_command(
	t_simple_command *cmd, t_tokenizer *tokenizer, enum e_syntax_error *error
) {
	while (true)
	{
		if (parse_cmd_arg(&cmd->argv, tokenizer, error))
			continue ;
		if (*error != SYNTAX_ERROR_NO_MATCH)
			return (false);
		if (parse_cmd_redir(&cmd->redirs, tokenizer, error))
			continue ;
		if (*error != SYNTAX_ERROR_NO_MATCH)
			return (false);
		break ;
	}
	return (cmd->argv.size);
}

// For when pipe has a single child
// 
// In this case, executables fork (and builtins don't)
// Then both are supposed to return normally
// /!\ There can also be 2 returns in case execve fails

bool	run_simple_command(
	t_simple_command *cmd, t_session *session, enum e_exec_error *error
) {
	t_vector		fields;
	t_backup_fds	backup;
	bool			status;

	if (!expand_all(cmd->argv, session->env, &fields))
		return (false);
	if (!save_backup_fds(&backup))
	{
		free_fields(fields);
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
	status = (run_cmd_redirs(cmd->redirs, error)
			&& run_raw_command(fields, session, backup, error));
	if (!restore_backup_fds(backup))
	{
		free_fields(fields);
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
	free_fields(fields);
	ft_oprintln(ft_stderr(), "Status: {u8}", session->last_status);
	return (status);
}

// For when pipe has multiple children
//
// In this case, executables don't fork (nor do builtins)
// Executables are not supposed to return, except if execve fails

void	start_simple_command(
	t_simple_command *cmd, t_session *session, enum e_exec_error *error
) {
	t_vector	fields;

	if (!expand_all(cmd->argv, session->env, &fields))
		return ;
	if (!run_cmd_redirs(cmd->redirs, error))
	{
		free_fields(fields);
		return ;
	}
	start_raw_command(fields, session, error);
	free_fields(fields);
}

void	free_simple_command(t_simple_command cmd)
{
	t_u32	i;

	i = 0;
	while (i < cmd.argv.size)
	{
		ft_string_free(((t_string *)cmd.argv.elems)[i]);
		i++;
	}
	ft_vector_free(cmd.argv);
	i = 0;
	while (i < cmd.redirs.size)
	{
		ft_string_free(
			((t_redirection *)cmd.redirs.elems)[i].filename);
		i++;
	}
	ft_vector_free(cmd.redirs);
}
