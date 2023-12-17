/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:38:29 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/17 19:05:10 by vchakhno         ###   ########.fr       */
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
	t_program				program;
	t_token					token;
	bool					status;
	enum e_program_error	error;

	(void) session;
	if (!alloc_program(&program))
		return (false);
	status = parse_token(&program, &token, MAIN_PROMPT, &error);
	while (true)
	{
		if (status)
		{
			if (ft_str_equal_c_str(token.content, "exit"))
				break ;
			print_token(token);
		}
		else if (error == ERROR_CTRL_D)
			ft_println("Syntax error");
		else if (error == ERROR_MALLOC)
			break ;
		status = parse_token(&program, &token, MAIN_PROMPT, &error);
	}
	free_program(program);
	return (true);
}

void	destroy_session(t_session *session)
{
	free_env(&session->env);
}
