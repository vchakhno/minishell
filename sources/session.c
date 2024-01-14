/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:38:29 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/14 16:03:39 by vchakhno         ###   ########.fr       */
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
	session->should_exit = false;
	session->exit_status = 0;
	rl_outstream = stderr;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	return (true);
}

bool	run_repl(t_session *session)
{
	t_ast_root				ast;
	enum e_syntax_error		syntax_error;
	bool					valid_ast;

	while (!session->should_exit)
	{
		if (!alloc_ast(&ast))
			break ;
		valid_ast = parse_ast(&ast, &session->lines, &syntax_error);
		if (!valid_ast && (syntax_error == SYNTAX_ERROR_MALLOC
				|| syntax_error == SYNTAX_ERROR_CTRL_D))
		{
			free_ast(ast);
			break ;
		}
		if (valid_ast || syntax_error == SYNTAX_ERROR_NO_MATCH)
		{
			register_command(session->lines);
			cut_lines(&session->lines);
		}
		if (valid_ast && !run_ast(ast, session))
		{
			free_ast(ast);
			break ;
		}
		free_ast(ast);
	}
	return (true);
}

void	destroy_session(t_session session)
{
	free_lines(session.lines);
	free_env(session.env);
}
