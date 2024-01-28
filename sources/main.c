/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:35:13 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 01:54:30 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "session.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **env)
{
	t_session	session;
	t_u8		exit_status;

	(void) argc, (void) argv;
	if (!init_session(&session, env))
		return (EXIT_FAILURE);
	exit_status = run_repl(&session);
	destroy_session(session);
	return (exit_status);
}
