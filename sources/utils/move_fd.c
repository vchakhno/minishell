/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:02:57 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 01:48:57 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

bool	move_fd(int from, int to)
{
	bool	status;

	if (from == to)
		return (true);
	status = (dup2(from, to) != -1);
	close(from);
	return (status);
}
