/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/29 08:12:55 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

bool	run_builtin_cat(t_vector argv, t_session *session)
{
	int		c;

	(void) argv;
	(void) session;
	while (read(STDIN_FILENO, &c, 1) == 1)
		write(STDOUT_FILENO, &c, 1);
	return (true);
}
