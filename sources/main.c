/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekhaled <ekhaled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:13:59 by ekhaled           #+#    #+#             */
/*   Updated: 2023/09/21 05:18:30 by ekhaled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	read_input(t_session *session, t_cstr *input)
{
	// readline("PS1")
}

bool	run_repl(t_session *session)
{
	t_ast			ast;
	t_cstr			input;
	t_token_queue	token_queue;

	while (!session->should_exit)
	{
		if (!read_input(session, &input.str))
			;
		generate_tokens(input, &token_queue);
		while (!token_queue)
		{
			generate_ast(&input, &token_queue, &ast);
			execute_ast(ast, session);
			free_ast(&ast);
		}
		free_input(&input);
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
