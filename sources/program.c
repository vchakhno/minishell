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

bool	alloc_program(t_program *program)
{
	return (ft_string_alloc(&program->str, 30));
}

bool	get_program(t_program *program, char *prompt)
{
	char	*user_input;
	
	// ft_oprintf(ft_stderr(), "minishell> ");
	user_input = readline(prompt);
	if (!user_input)
	{
		ft_oprintln(ft_stderr(), "Error: Couldn't get user program");
		return (false);
	}
	if (!ft_string_reserve(&program->str, ft_c_str_len(user_input) + 1))
	{
		ft_oprintln(ft_stderr(), "Error: Not enough memory to store user program");
		free(user_input);
		return (false);
	}
	ft_string_append_c_str(&program->str, user_input);
	ft_string_append_c_str(&program->str, "\n");
	free(user_input);
	program->str.c_str[program->str.len] = '\0';
	return (true);
}

void	cut_program(t_program *program, t_command command)
{
	ft_string_remove_slice(&program->str, 0, command.text.len + 1);
}

void	free_program(t_program program)
{
	ft_string_free(program.str);
}
