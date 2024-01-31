/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:55:05 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 00:50:12 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_input.h"
#include "prompts.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

t_read_input_status	append_lines(
	t_shell_input *input, const char *prompt, t_u8 *exit_status
) {
	t_read_input_status	status;
	t_string			user_input;

	if (input->cursor == 0)
		prompt = MAIN_PROMPT;
	status = read_input(&user_input, prompt, exit_status);
	if (status != READING_SUCCEEDED)
		return (status);
	if (!ft_string_reserve(&input->text, user_input.len + 1))
	{
		ft_eprintln("Error: Not enough memory to store user lines");
		ft_string_free(user_input);
		return (READING_CANCELED);
	}
	ft_string_append_str(&input->text, user_input.str);
	ft_string_append_c_str(&input->text, "\n");
	ft_string_free(user_input);
	return (READING_SUCCEEDED);
}

t_read_input_status	read_line(
	t_shell_input *input, t_str *line, const char *prompt, t_u8 *exit_status
) {
	t_read_input_status	status;
	t_u32				i;

	if (input->cursor == input->text.len)
	{
		status = append_lines(input, prompt, exit_status);
		if (status != READING_SUCCEEDED)
			return (status);
	}
	i = 0;
	while (input->cursor + i < input->text.len
		&& input->text.c_str[input->cursor + i] != '\n')
		i++;
	line->c_str = &input->text.c_str[input->cursor];
	line->len = i + 1;
	input->cursor += i + 1;
	return (READING_SUCCEEDED);
}

void	register_command(t_shell_input input)
{
	input.text.c_str[input.cursor - 1] = '\0';
	add_history(input.text.c_str);
}

void	cut_lines(t_shell_input *input)
{
	ft_string_remove_slice(&input->text, 0, input->cursor);
	input->cursor = 0;
}
