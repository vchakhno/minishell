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
#include <readline/readline.h>
#include <readline/history.h>

bool	alloc_program(t_program *program)
{
	if (!ft_string_alloc(&program->text, 30))
		return (false);
	program->cmd_cursor = 0;
	return (true);
}

bool	get_program(t_program *program, char *prompt)
{
	char	*user_input;
	
	user_input = readline(prompt);
	if (!user_input)
	{
		ft_oprintln(ft_stderr(), "Error: Couldn't get user program");
		return (false);
	}
	if (!ft_string_reserve(&program->text, ft_c_str_len(user_input) + 1))
	{
		ft_oprintln(ft_stderr(), "Error: Not enough memory to store user program");
		free(user_input);
		return (false);
	}
	ft_string_append_c_str(&program->text, user_input);
	ft_string_append_c_str(&program->text, "\n");
	free(user_input);
	return (true);
}

void	register_command(t_program program)
{
	program.text.c_str[program.cmd_cursor] = '\0';
	add_history(program.text.c_str);
}

void	cut_program(t_program *program)
{
	ft_string_remove_slice(&program->text, 0, program->cmd_cursor + 1);
	program->cmd_cursor = 0;
}

void	free_program(t_program program)
{
	ft_string_free(program.text);
}
