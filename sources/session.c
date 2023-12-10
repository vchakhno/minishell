/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:38:29 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/10 19:55:13 by vchakhno         ###   ########.fr       */
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
	t_command	command;

	if (!alloc_program(&program))
		return (false);
	while (!session->should_exit)
	{
		if (!parse_command(&command, &program))
		{
			ft_oprintln(ft_stderr(), "Error: Command parsing failed");
			free_program(program);
			return (false);
		}
		register_command(command);
		if (!execute_command(&command, session))
		{
			ft_oprintln(ft_stderr(), "Error: Command execution failed");
			free_command(command);
			free_program(program);
			return (false);
		}
		free_command(command);
		cut_program(&program, command);
	}
	free_program(program);
	return (true);
}

void	destroy_session(t_session *session)
{
	free_env(&session->env);
}
