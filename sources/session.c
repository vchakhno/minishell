/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:38:29 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 09:10:17 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "session.h"

bool	setup_session(t_session *session, char **env)
{
	if (!alloc_shell_input(&session->shell_input))
		return (false);
	if (!alloc_runtime_context(&session->runtime_context, env))
	{
		free_shell_input(session->shell_input);
		return (false);
	}
	return (true);
}

t_u8	run_repl(t_session *session)
{
	t_ast_root	ast;

	while (true)
	{
		if (!get_complete_ast(&session->shell_input, &ast)
			|| !run_ast(ast, &session->runtime_context))
		{
			free_ast(ast);
			break ;
		}
		free_ast(ast);
	}
	return (session->runtime_context.exit_status);
}

void	quit_session(t_session session)
{
	free_runtime_context(session.runtime_context);
	free_shell_input(session.shell_input);
}
