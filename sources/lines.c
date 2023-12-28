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

bool	append_lines(
	t_lines *lines, const char *prompt, enum e_prompt_error *error
) {
	t_string	user_input;

	if (lines->cursor == 0)
		prompt = MAIN_PROMPT;
	if (!read_input(&user_input, prompt, error))
		return (false);
	if (!ft_string_reserve(&lines->text, user_input.len + 1))
	{
		ft_eprintln("Error: Not enough memory to store user lines");
		ft_string_free(user_input);
		*error = PROMPT_ERROR_MALLOC;
		return (false);
	}
	ft_string_append_str(&lines->text, user_input.str);
	ft_string_append_c_str(&lines->text, "\n");
	ft_string_free(user_input);
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
