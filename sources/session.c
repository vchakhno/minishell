/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:38:29 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/26 03:22:07 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

bool	init_session(t_session *session, char **env)
{
	if (!parse_env(&session->env, env))
		return (false);
	if (!alloc_lines(&session->lines))
	{
		free_env(session->env);
		return (false);
	}
	session->exit_status = 0;
	rl_outstream = stderr;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	return (true);
}

// true -> continue
// false -> exit
// bool	parse_cancellable_ast(t_ast_root *ast, t_lines *lines, bool *valid)
// {
// 	bool	cancelled;

// 	if (!parse_ast(ast, lines, valid, &cancelled))
// 		return (false);
// 	while (cancelled)
// 	{
// 		if (!parse_ast(ast, lines, valid, &cancelled))
// 			return (false);
// 	}
// 	return (true);
// }

bool	parse_cancellable_ast(t_ast_root *ast, t_lines *lines, bool *valid)
{
	enum e_parsing_error	error;
	bool					ok;
	bool					cancelled;

	ok = parse_ast(ast, lines, &error);
	cancelled = (!ok && error == PARSING_ERROR_CANCEL);
	while (cancelled)
	{
		cut_lines(lines);
		ok = parse_ast(ast, lines, &error);
		cancelled = (!ok && error == PARSING_ERROR_CANCEL);
	}
	*valid = (ok || error != PARSING_ERROR_SYNTAX);
	return (ok || error == PARSING_ERROR_SYNTAX);
}

// true -> continue
// false -> exit
bool	parse_validated_ast(t_ast_root *ast, t_lines *lines)
{
	bool	valid;

	valid = false;
	while (!valid)
	{
		if (!parse_cancellable_ast(ast, lines, &valid))
			return (false);
		register_command(*lines);
		cut_lines(lines);
	}
	return (true);
}

void	run_repl(t_session *session)
{
	t_ast_root	ast;

	while (true)
	{
		if (!alloc_ast(&ast))
			break ;
		if (!parse_validated_ast(&ast, &session->lines)
			|| !run_ast(ast, session))
		{
			free_ast(ast);
			break ;
		}
		free_ast(ast);
	}
}

void	destroy_session(t_session session)
{
	free_lines(session.lines);
	free_env(session.env);
	clear_history();
}
