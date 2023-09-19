/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekhaled <ekhaled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:13:59 by ekhaled           #+#    #+#             */
/*   Updated: 2023/09/19 18:40:19 by ekhaled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	run_repl(t_session *session)
{
	char	*line;
	t_ast	ast;

	while (!session->should_exit)
	{
		read_line(session, &line);//only takes one line
		line_to_ast(line, &ast);
		execute_ast(ast, session);
	}
}

int	main(void)
{
	t_session	session;

	if (!init_session(&session))
		return (EXIT_FAILURE);
	if (!run_repl(&session))
		return (EXIT_FAILURE);
	if (!destroy_session(&session))
		return (EXIT_FAILURE);
	return (session.last_cmd_status);
}
