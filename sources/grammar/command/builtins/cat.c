/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/30 03:44:33 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

bool	run_builtin_cat(t_vector argv, t_env *env, t_u8 *exit_status)
{
	int		c;

	(void) argv;
	(void) env;
	while (read(STDIN_FILENO, &c, 1) == 1)
		write(STDOUT_FILENO, &c, 1);
	return (builtin_ok(exit_status));
}
