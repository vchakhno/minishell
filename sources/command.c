/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:51:17 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/10 22:19:12 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>

bool	parse_command(t_command *command, t_program *program)
{
	if (!program->str.len && !get_program(program, "minishell> "))
	{
		ft_oprintln(ft_stderr(), "Error: Couldn't read user input");
		return (false);
	}
	if (!ft_vector_alloc(&command->tokens, sizeof(t_token), 30))
		return (false);
	command->text = program->str.str;
	ft_str_find_char(program->str.str, '\n', &command->text.len);
	command->tokens_pos = 0;
	return (true);
}

void	register_command(t_command command)
{
	command.text.c_str[command.text.len] = '\0';
	add_history(command.text.c_str);
}

bool	execute_command(t_command *command, t_session *session)
{
	(void) command;
	(void) session;
	ft_println("Command: {str}", command->text);
	return (true);
}

void	free_command(t_command command)
{
	ft_vector_free(command.tokens);
}

