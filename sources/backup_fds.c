/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 01:42:26 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/21 14:19:16 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

bool	save_backup_fds(t_backup_fds *backup)
{
	backup->stdin = dup(STDIN_FILENO);
	if (backup->stdin == -1)
		return (false);
	backup->stdout = dup(STDOUT_FILENO);
	if (backup->stdout == -1)
	{
		close(backup->stdin);
		return (false);
	}
	return (true);
}

bool	restore_backup_fds(t_backup_fds backup)
{
	bool	error;

	error = dup2(backup.stdin, STDIN_FILENO) == -1;
	close(backup.stdin);
	error = (dup2(backup.stdout, STDOUT_FILENO) == -1 || error);
	close(backup.stdout);
	return (!error);
}

void	discard_backup_fds(t_backup_fds backup)
{
	close(backup.stdin);
	close(backup.stdout);
}
