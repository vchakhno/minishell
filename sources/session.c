/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:38:29 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/21 18:41:07 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <readline/readline.h>
#include <readline/history.h>

bool	init_session(t_session *session, char **env)
{
	if (!parse_env(&session->env, env))
		return (false);
	if (!alloc_lines(&session->lines))
	{
		free_env(session->env);
		return (false);
	}
	session->last_status = 0;
	rl_outstream = stderr;
	return (true);
}

bool	run_repl(t_session *session)
{
	t_ast_root				ast;
	enum e_syntax_error		syntax_error;
	enum e_exec_error		exec_error;
	bool					valid_ast;

	(void) session;
	while (true)
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
		if (valid_ast && !execute_ast(ast, session, &exec_error)
			&& exec_error == EXEC_ERROR_EXIT)
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
