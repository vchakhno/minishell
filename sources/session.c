/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:38:29 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 01:57:58 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "session.h"
#include "grammar.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

bool	init_session(t_session *session, char **env)
{
	if (!parse_env(&session->runtime_context.env, env))
		return (false);
	if (!alloc_lines(&session->shell_input))
	{
		free_env(session->runtime_context.env);
		return (false);
	}
	session->runtime_context.exit_status = 0;
	rl_outstream = stderr;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	return (true);
}

bool	parse_cancellable_ast(
	t_ast_root *ast, t_shell_input *input, bool *valid
) {
	enum e_parsing_error	error;
	bool					ok;
	bool					cancelled;

	ok = parse_ast(ast, input, &error);
	cancelled = (!ok && error == PARSING_ERROR_CANCEL);
	while (cancelled)
	{
		cut_lines(input);
		ok = parse_ast(ast, input, &error);
		cancelled = (!ok && error == PARSING_ERROR_CANCEL);
	}
	*valid = (ok || error != PARSING_ERROR_SYNTAX);
	return (ok || error == PARSING_ERROR_SYNTAX);
}

// true -> continue
// false -> exit
bool	parse_validated_ast(t_ast_root *ast, t_shell_input *input)
{
	bool	valid;

	valid = false;
	while (!valid)
	{
		if (!parse_cancellable_ast(ast, input, &valid))
			return (false);
		register_command(*input);
		cut_lines(input);
	}
	return (true);
}

t_u8	run_repl(t_session *session)
{
	t_ast_root	ast;

	while (true)
	{
		if (!alloc_ast(&ast))
			break ;
		if (!parse_validated_ast(&ast, &session->shell_input)
			|| !run_ast(ast, &session->runtime_context))
		{
			free_ast(ast);
			break ;
		}
		free_ast(ast);
	}
	return (session->runtime_context.exit_status);
}

void	destroy_session(t_session session)
{
	free_lines(session.shell_input);
	free_env(session.runtime_context.env);
	clear_history();
}
