/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:38:29 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 10:49:27 by vchakhno         ###   ########.fr       */
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
	enum e_syntax_error		error;

	(void) session;
	if (!alloc_lines(&lines))
		return (false);
	while (true)
	{
		if (!alloc_ast(&ast))
			break ;
		if (!parse_ast(&ast, &lines, &error))
		{
			free_ast(ast);
			break ;
		}
		register_command(lines);
		cut_lines(&lines);
		execute_ast(ast, session);
		free_ast(ast);
	}
	free_lines(lines);
	return (true);
}

void	destroy_session(t_session *session)
{
	free_env(&session->env);
}
