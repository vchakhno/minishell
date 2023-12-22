/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:02:57 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/22 15:54:11 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

bool	move_fd(int from, int to)
{
	bool	status;

	if (from == to)
		return (true);
	status = (dup2(from, to) == -1);
	close(from);
	return (status);
}
