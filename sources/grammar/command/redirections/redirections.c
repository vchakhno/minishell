/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 01:13:54 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

bool	parse_redirections(
	t_vector *redirs, t_tokenizer *tokenizer, enum e_parsing_error *error
) {
	t_redirection	redir;

	if (!parse_redirection(&redir, tokenizer, error))
		return (false);
	if (!ft_vector_push(redirs, &redir))
	{
		print_error("redirection: out of memory");
		*error = PARSING_ERROR_CANCEL;
		return (false);
	}
	return (true);
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
