/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 01:42:26 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/22 15:54:31 by vchakhno         ###   ########.fr       */
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
	return (
		move_fd(backup.stdin, STDIN_FILENO)
		& (int) move_fd(backup.stdout, STDOUT_FILENO)
	);
}

void	discard_backup_fds(t_backup_fds backup)
{
	close(backup.stdin);
	close(backup.stdout);
}
