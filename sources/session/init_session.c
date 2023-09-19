/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_session.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekhaled <ekhaled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:40:51 by ekhaled           #+#    #+#             */
/*   Updated: 2023/09/12 16:47:37 by ekhaled          ###   ########.fr       */
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
	session->is_interactive = (isatty(STDIN_FILENO) && isatty(STDERR_FILENO));
	session->should_exit = false;
}
