/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 07:37:26 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"
#include <unistd.h>

bool	run_builtin_env(t_vector argv, t_env *env, t_u8 *exit_status)
{
	(void) argv;
	if (argv.size != 1)
	{
		print_error("env: No arguments expected");
		return (builtin_error(exit_status));
	}
	display_env(*env);
	return (builtin_ok(exit_status));
}
