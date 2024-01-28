/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 06:00:59 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"
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

t_parsing_status	parse_pipeline(t_vector *pipeline, t_tokenizer *tokenizer)
{
	t_parsing_status	status;
	t_simple_command	command;

	status = PARSING_SUCCEEDED;
	while (status != PARSING_FAILED)
	{
		if (!alloc_simple_command(&command))
			return (PARSING_CANCELED);
		status = parse_simple_command(&command, tokenizer);
		if (status != PARSING_SUCCEEDED)
		{
			free_simple_command(command);
			return (status);
		}
		if (!ft_vector_push(pipeline, &command))
		{
			free_simple_command(command);
			return (PARSING_CANCELED);
		}
		status = match_token(tokenizer, "|", "pipe>");
		if (status == PARSING_CANCELED || status == PARSING_EXITED)
			return (status);
	}
	return (PARSING_SUCCEEDED);
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
