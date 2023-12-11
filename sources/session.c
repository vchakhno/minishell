/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:38:29 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/11 10:01:52 by vchakhno         ###   ########.fr       */
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
	t_program	program;
	t_ast		ast;

	if (!alloc_program(&program))
		return (false);
	while (!session->should_exit)
	{
		if (!parse_ast(&ast, &program))
		{
			ft_oprintln(ft_stderr(), "Error: Command parsing failed");
			free_program(program);
			return (false);
		}
		register_command(program);
		if (!execute_ast(ast, session))
		{
			ft_oprintln(ft_stderr(), "Error: Command execution failed");
			free_ast(ast);
			free_program(program);
			return (false);
		}
		free_ast(ast);
		cut_program(&program);
	}
	free_program(program);
	return (true);
}

void	destroy_session(t_session *session)
{
	free_env(&session->env);
}
