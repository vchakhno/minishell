/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:38:29 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/01 01:52:03 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <readline/readline.h>

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

	while (!session->should_exit)
	{
		if (!alloc_program(&program))
			return (false);
		if (!get_program(&program, "minishell> "))
		{
			free_program(program);
			return (false);
		}
		// if (!execute_program(&program, session))
		// {
		// 	free_program(program);
		// 	return (false);
		// }
		ft_println("User input: {str}", program.str.str);
		free_program(program);
	}
	return (true);
}

void	destroy_session(t_session *session)
{
	free_env(&session->env);
}
