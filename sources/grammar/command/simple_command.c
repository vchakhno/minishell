/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 04:18:44 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"
#include "expand.h"
#include <unistd.h>

bool	alloc_simple_command(t_simple_command *cmd)
{
	if (!ft_vector_alloc(&cmd->argv, sizeof(t_string), 10))
		return (false);
	if (!ft_vector_alloc(&cmd->redirs, sizeof(t_redirection), 2))
	{
		ft_vector_free(cmd->argv);
		return (false);
	}
	return (true);
}

t_parsing_status	parse_simple_command(
	t_simple_command *cmd, t_tokenizer *tokenizer, t_u8 *exit_status
) {
	t_parsing_status	status;
	enum e_redir_type	type;

	status = PARSING_SUCCEEDED;
	while (status != PARSING_FAILED)
	{
		status = parse_argument(&cmd->argv, tokenizer, exit_status);
		if (status == PARSING_SUCCEEDED)
			continue ;
		if (status != PARSING_FAILED)
			return (status);
		status = match_redir_op(tokenizer, &type, exit_status);
		if (status == PARSING_FAILED)
			continue ;
		if (status != PARSING_SUCCEEDED)
			return (status);
		status = parse_redirections(&cmd->redirs, tokenizer, type, exit_status);
		if (status != PARSING_SUCCEEDED)
			return (status);
	}
	if (!cmd->argv.size)
		return (PARSING_FAILED);
	return (PARSING_SUCCEEDED);
}

// In this case, executables fork (and builtins don't)
// Then both are supposed to return normally
// /!\ There will be multiple returns if the command contains heredocs,
// or execve fails

bool	run_simple_command(t_simple_command cmd, t_runtime_context *context)
{
	t_vector		fields;
	t_backup_fds	backup;
	bool			redir_recovers;
	bool			cmd_recovers;

	if (!expand_args(cmd.argv, *context, &fields))
	{
		context->exit_status = 1;
		return (true);
	}
	if (!run_redirections(cmd.redirs, &backup, &redir_recovers, *context))
	{
		context->exit_status = 1;
		free_fields_vec(fields);
		return (redir_recovers);
	}
	cmd_recovers = run_raw_command(fields, context, backup);
	cleanup_redirections(cmd.redirs, backup, cmd.redirs.size);
	free_fields_vec(fields);
	return (cmd_recovers);
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
	free_redirections(cmd.redirs);
}
