/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 01:42:26 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 00:20:55 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "utils.h"
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
	return (
		move_fd(backup.stdin, STDIN_FILENO)
		& (int) move_fd(backup.stdout, STDOUT_FILENO)
	);
}

void	discard_backup_fds(t_backup_fds backup)
{
	if (backup.stdin != STDIN_FILENO)
		close(backup.stdin);
	if (backup.stdout != STDOUT_FILENO)
		close(backup.stdout);
}
