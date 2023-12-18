/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:35:13 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 20:59:46 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **env)
{
	t_session	session;

	(void) argc, (void) argv;
	if (!init_session(&session, env))
		return (EXIT_FAILURE);
	if (!run_repl(&session))
	{
		destroy_session(session);
		return (EXIT_FAILURE);
	}
	destroy_session(session);
}
