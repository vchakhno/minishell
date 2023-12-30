/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:17:41 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/30 02:17:49 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_ok(t_u8 *exit_status)
{
	*exit_status = 0;
	return (true);
}

bool	builtin_error(t_u8 *exit_status)
{
	*exit_status = 1;
	return (true);
}
