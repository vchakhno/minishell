/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 00:39:21 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

t_parsing_status	parse_redirections(
	t_vector *redirs, t_tokenizer *tokenizer, enum e_redir_type type,
	t_u8 *exit_status
) {
	t_parsing_status	status;
	t_redirection		redir;

	redir.type = type;
	status = parse_redirection(&redir, tokenizer, exit_status);
	if (status != PARSING_SUCCEEDED)
		return (status);
	if (!ft_vector_push(redirs, &redir))
	{
		print_error("redirection: out of memory");
		return (PARSING_CANCELED);
	}
	return (PARSING_SUCCEEDED);
}

bool	run_redirections(
	t_vector redirs, t_backup_fds *backup, bool *recovers,
	t_runtime_context context
) {
	t_redirection	*redir;
	t_u32			i;

	if (!save_backup_fds(backup))
	{
		*recovers = true;
		return (false);
	}
	i = 0;
	while (i < redirs.size)
	{
		redir = &((t_redirection *)redirs.elems)[i];
		if (!run_redirection(redir, recovers, context))
		{
			if (*recovers)
				cleanup_redirections(redirs, *backup, i);
			return (false);
		}
		i++;
	}
	return (true);
}

void	cleanup_redirections(t_vector redirs, t_backup_fds backup, t_u32 size)
{
	t_u32	i;

	i = 0;
	while (i < size)
	{
		cleanup_redirection(((t_redirection *)redirs.elems)[i]);
		i++;
	}
	restore_backup_fds(backup);
}

void	free_redirections(t_vector redirs)
{
	t_u32	i;

	i = 0;
	while (i < redirs.size)
	{
		free_redirection(((t_redirection *)redirs.elems)[i]);
		i++;
	}
	ft_vector_free(redirs);
}
