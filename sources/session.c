/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:38:29 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 21:40:56 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <readline/readline.h>
#include <readline/history.h>

bool	init_session(t_session *session, char **env)
{
	if (!parse_env(&session->env, env))
		return (false);
	session->should_exit = false;
	rl_outstream = stderr;
	return (true);
}

bool	run_repl(t_session *session)
{
	t_lines					lines;
	t_ast_root				ast;
	enum e_syntax_error		syntax_error;
	enum e_exec_error		exec_error;

	(void) session;
	if (!alloc_lines(&lines))
		return (false);
	while (true)
	{
		if (!alloc_ast(&ast))
			break ;
		if (!parse_ast(&ast, &lines, &syntax_error))
		{
			free_ast(ast);
			break ;
		}
		register_command(lines);
		cut_lines(&lines);
		if (!execute_ast(ast, session, &exec_error) && exec_error == EXEC_ERROR_EXIT)
		{
			free_ast(ast);
			break ;
		}
		free_ast(ast);
	}
	free_lines(lines);
	return (true);
}

void	destroy_session(t_session session)
{
	free_env(session.env);
}
