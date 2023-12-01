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
	if (!ft_string_alloc(&program->str, 30))
		return (false);
	program->cursor = 0;
	return (true);
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
	if (!ft_string_append_c_str(&program->str, user_input))
	{
		ft_oprintln(ft_stderr(), "Error: Not enough memory to store user program");
		free(user_input);
		return (false);
	}
	free(user_input);
	return (true);
}

void	free_program(t_program program)
{
	ft_string_free(program.str);
}
