/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 00:24:15 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
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
