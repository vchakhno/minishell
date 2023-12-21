/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                       :+:      :+:    :+:   */
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

bool	alloc_lines(t_lines *lines)
{
	if (!ft_string_alloc(&lines->text, 30))
		return (false);
	lines->cursor = 0;
	return (true);
}

bool	g_ctrlc = false;

void	sigint_hook(int sig)
{
	(void) sig;
	close(STDIN_FILENO);
	g_ctrlc = true;
}

bool	read_lines(
	t_lines *lines, const char *prompt, enum e_prompt_error *error
) {
	static bool	first_ctrl_c = true;
	char		*user_input;
	int			new_stdin;

	// pre readline
	new_stdin = dup(STDIN_FILENO);
	if (new_stdin == -1)
	{
		*error = PROMPT_ERROR_MALLOC;
		return (false);
	}
	signal(SIGINT, &sigint_hook);

	if (lines->cursor == 0)
		prompt = MAIN_PROMPT;
	user_input = readline(prompt);
	// post readline
	signal(SIGINT, SIG_DFL);
	if (dup2(new_stdin, STDIN_FILENO) == -1)
	{
		*error = PROMPT_ERROR_MALLOC;
		return (false);
	}
	close(new_stdin);

	if (!user_input)
	{
		if (g_ctrlc)
		{
			g_ctrlc = false;
			*error = PROMPT_ERROR_CTRL_C;
			if (first_ctrl_c)
				ft_oprintln(ft_stderr(), "");
			first_ctrl_c = false;
		}
		else
		{
			*error = PROMPT_ERROR_CTRL_D;
			first_ctrl_c = true;
		}
		return (false);
	}
	first_ctrl_c = true;
	if (!ft_string_reserve(&lines->text, ft_c_str_len(user_input) + 1))
	{
		ft_oprintln(ft_stderr(), "Error: Not enough memory to store user lines");
		free(user_input);
		*error = PROMPT_ERROR_MALLOC;
		return (false);
	}
	ft_string_append_c_str(&lines->text, user_input);
	ft_string_append_c_str(&lines->text, "\n");
	free(user_input);
	return (true);
}

void	register_command(t_lines lines)
{
	lines.text.c_str[lines.cursor - 1] = '\0';
	add_history(lines.text.c_str);
}

void	cut_lines(t_lines *lines)
{
	ft_string_remove_slice(&lines->text, 0, lines->cursor);
	lines->cursor = 0;
}

void	free_lines(t_lines lines)
{
	ft_string_free(lines.text);
}
