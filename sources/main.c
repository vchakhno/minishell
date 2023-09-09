/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekhaled <ekhaled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:13:59 by ekhaled           #+#    #+#             */
/*   Updated: 2023/09/08 17:32:58 by ekhaled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	init_session(t_session *session)
{
	if (!init_history(&session->history))
		;
	if (!init_env(&session->env))
		;
	session->last_cmd_status = 0;

}

int	main(void)
{
	t_session	session;

	if (!init_session(&session))
		;
	
}
