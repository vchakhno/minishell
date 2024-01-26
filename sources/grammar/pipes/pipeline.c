/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/26 17:23:27 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

bool	alloc_pipeline(t_vector *pipeline)
{
	if (!ft_vector_alloc(pipeline, sizeof(t_simple_command), 8))
		return (false);
	return (true);
}

bool	parse_pipeline(
	t_vector *pipeline, t_tokenizer *tokenizer, enum e_parsing_error *error
) {
	t_simple_command	command;

	while (true)
	{
		if (!alloc_simple_command(&command))
		{
			*error = PARSING_ERROR_CANCEL;
			return (false);
		}
		if (!parse_simple_command(&command, tokenizer, error))
		{
			free_simple_command(command);
			return (false);
		}
		if (!ft_vector_push(pipeline, &command))
		{
			free_simple_command(command);
			*error = PARSING_ERROR_CANCEL;
			return (false);
		}
		if (!match_token(tokenizer, "|", "pipe>", error))
			return (*error == PARSING_ERROR_SYNTAX);
	}
	return (true);
}

void	free_pipeline(t_vector pipeline)
{
	t_u32	i;

	i = 0;
	while (i < pipeline.size)
	{
		free_simple_command(((t_simple_command *)pipeline.elems)[i]);
		i++;
	}
	ft_vector_free(pipeline);
}
