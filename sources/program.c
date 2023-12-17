/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:55:05 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/01 01:13:57 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

bool	alloc_program(t_program *program)
{
	if (!ft_string_alloc(&program->text, 30))
		return (false);
	program->cursor = 0;
	return (true);
}

bool	g_ctrlc = false;

void	sigint_hook(int sig)
{
	(void) sig;
	close(STDIN_FILENO);
	g_ctrlc = true;
}

bool	get_program_lines(
	t_program *program, const char *prompt, enum e_program_error *error
) {
	char	*user_input;
	int		new_stdin;
	
	// pre readline
	new_stdin = dup(STDIN_FILENO);
	signal(SIGINT, &sigint_hook);

	rl_on_new_line();
	user_input = readline(prompt);
	
	// post readline
	signal(SIGINT, SIG_DFL);
	dup2(new_stdin, STDIN_FILENO);
	close(new_stdin);

	if (!user_input)
	{
		if (g_ctrlc)
		{
			g_ctrlc = false;
			*error = ERROR_CTRL_C;
		}
		else
			*error = ERROR_CTRL_D;
		return (false);
	}
	if (!ft_string_reserve(&program->text, ft_c_str_len(user_input) + 1))
	{
		ft_oprintln(ft_stderr(), "Error: Not enough memory to store user program");
		free(user_input);
		*error = ERROR_MALLOC;
		return (false);
	}
	ft_string_append_c_str(&program->text, user_input);
	ft_string_append_c_str(&program->text, "\n");
	free(user_input);
	return (true);
}

void	register_command(t_program program)
{
	program.text.c_str[program.cursor] = '\0';
	add_history(program.text.c_str);
}

void	cut_program(t_program *program)
{
	ft_string_remove_slice(&program->text, 0, program->cursor + 1);
	program->cursor = 0;
}

void	free_program(t_program program)
{
	ft_string_free(program.text);
}
