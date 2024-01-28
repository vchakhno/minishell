/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_input.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 02:05:58 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_INPUT_H
# define SHELL_INPUT_H

# include <stdbool.h>
# include <libft/libft.h>

/* ************************************************************************** */
/* LINES																	  */
/* ************************************************************************** */

typedef struct s_shell_input
{
	t_string	text;
	t_u32		cursor;
}	t_shell_input;

enum	e_prompt_error
{
	PROMPT_ERROR_CANCEL,
	PROMPT_ERROR_EXIT,
};

bool	read_input(t_string *new_lines, const char *prompt,
			enum e_prompt_error *error);

bool	alloc_shell_input(t_shell_input *input);
bool	append_lines(t_shell_input *input, const char *prompt,
			enum e_prompt_error *error);
bool	read_line(t_shell_input *input, t_str *line, const char *prompt,
			enum e_prompt_error *error);
void	register_command(t_shell_input input);
void	cut_lines(t_shell_input *input);
void	free_shell_input(t_shell_input input);

#endif