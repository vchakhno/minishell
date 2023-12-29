/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:01:02 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/29 07:48:38 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

bool	parse_redirections(
	t_vector *redirs, t_tokenizer *tokenizer, enum e_syntax_error *error
) {
	t_redirection	redir;

	if (!parse_redirection(&redir, tokenizer, error))
		return (false);
	if (!ft_vector_push(redirs, &redir))
	{
		print_error("redirection: out of memory");
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	return (true);
}

bool	run_redirections(
	t_vector redirs, t_backup_fds *backup, enum e_exec_error *error
) {
	t_redirection	*redir;
	t_u32			i;

	if (!save_backup_fds(backup))
	{
		*error = EXEC_ERROR_RECOVER;
		return (false);
	}
	i = 0;
	while (i < redirs.size)
	{
		redir = &((t_redirection *)redirs.elems)[i];
		if (!run_redirection(redir, error))
		{
			if (*error == EXEC_ERROR_RECOVER)
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
