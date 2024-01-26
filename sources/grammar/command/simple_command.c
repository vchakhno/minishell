/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/26 03:17:14 by vchakhno         ###   ########.fr       */
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
	t_simple_command *cmd, t_tokenizer *tokenizer, enum e_parsing_error *error
) {
	while (true)
	{
		if (parse_argument(&cmd->argv, tokenizer, error))
			continue ;
		if (*error != PARSING_ERROR_SYNTAX)
			return (false);
		if (parse_redirections(&cmd->redirs, tokenizer, error))
			continue ;
		if (*error != PARSING_ERROR_SYNTAX)
			return (false);
		break ;
	}
	return (cmd->argv.size);
}

// In this case, executables fork (and builtins don't)
// Then both are supposed to return normally
// /!\ There will be multiple returns if the command contains heredocs,
// or execve fails

bool	run_simple_command(t_simple_command *cmd, t_env *env, t_u8 *exit_status)
{
	t_vector		fields;
	t_backup_fds	backup;
	bool			redir_recovers;

	if (!expand_all(cmd->argv, *env, *exit_status, &fields))
	{
		*exit_status = 1;
		return (true);
	}
	if (!run_redirections(cmd->redirs, &backup, &redir_recovers))
	{
		*exit_status = 1;
		free_fields_vec(fields);
		return (redir_recovers);
	}
	if (!run_raw_command(fields, env, backup, exit_status))
	{
		free_fields_vec(fields);
		return (false);
	}
	cleanup_redirections(cmd->redirs, backup, cmd->redirs.size);
	free_fields_vec(fields);
	ft_eprintln("[DEBUG] `{str}` status: {u8}",
		((t_string *)cmd->argv.elems)[0].str, *exit_status);
	return (true);
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
		free_redirection(((t_redirection *)cmd.redirs.elems)[i]);
		i++;
	}
	ft_vector_free(cmd.redirs);
}
