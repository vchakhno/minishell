/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_input.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 00:37:37 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_INPUT_H
# define SHELL_INPUT_H

# include <stdbool.h>
# include <libft/libft.h>

typedef enum e_read_input_status
{
	READING_SUCCEEDED,
	READING_CANCELED,
	READING_EXITED,
}	t_read_input_status;

typedef struct s_shell_input
{
	t_string	text;
	t_u32		cursor;
}	t_shell_input;

t_read_input_status	read_input(t_string *new_lines, const char *prompt,
						t_u8 *exit_status);

bool				alloc_shell_input(t_shell_input *input);
t_read_input_status	append_lines(t_shell_input *input, const char *prompt,
						t_u8 *exit_status);
t_read_input_status	read_line(t_shell_input *input, t_str *line,
						const char *prompt, t_u8 *exit_status);
void				register_command(t_shell_input input);
void				cut_lines(t_shell_input *input);
void				free_shell_input(t_shell_input input);

#endif