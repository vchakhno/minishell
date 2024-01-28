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

#include "shell_input.h"
#include "prompts.h"
#include "utils.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

static bool	g_ctrlc = false;

void	sigint_hook(int sig)
{
	(void) sig;
	close(STDIN_FILENO);
	g_ctrlc = true;
}

bool	setup_input(int *stdin_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	if (*stdin_backup == -1)
		return (false);
	signal(SIGINT, &sigint_hook);
	return (true);
}

bool	restore_input(int stdin_backup)
{
	signal(SIGINT, SIG_IGN);
	return (move_fd(stdin_backup, STDIN_FILENO));
}

t_read_input_status	handle_empty_input(bool *prev_ctrl_c)
{
	if (g_ctrlc)
	{
		g_ctrlc = false;
		if (!*prev_ctrl_c)
			ft_eprintln("");
		*prev_ctrl_c = true;
		return (READING_CANCELED);
	}
	*prev_ctrl_c = false;
	return (READING_EXITED);
}

t_read_input_status	read_input(t_string *new_lines, const char *prompt)
{
	static bool	prev_ctrl_c = false;
	char		*user_input;
	t_u32		input_len;
	int			stdin_backup;

	if (!setup_input(&stdin_backup))
		return (READING_CANCELED);
	user_input = readline(prompt);
	if (!restore_input(stdin_backup))
		return (READING_CANCELED);
	if (!user_input)
		return (handle_empty_input(&prev_ctrl_c));
	prev_ctrl_c = false;
	input_len = ft_c_str_len(user_input);
	*new_lines = (t_string){{{user_input, input_len}}, input_len + 1};
	return (READING_SUCCEEDED);
}
