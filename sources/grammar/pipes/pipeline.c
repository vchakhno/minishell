/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 11:48:45 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

bool	alloc_pipeline(t_pipeline *pipeline)
{
	if (!ft_vector_alloc(pipeline, sizeof(t_simple_command), 8))
		return (false);
	return (true);
}

t_parsing_status	parse_pipeline_elem(
	t_pipeline *pipeline, t_tokenizer *tokenizer
) {
	t_simple_command	command;
	t_parsing_status	status;

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
	return (PARSING_SUCCEEDED);
}

t_parsing_status	parse_pipeline(t_pipeline *pipeline, t_tokenizer *tokenizer)
{
	t_parsing_status	status;

	while (true)
	{
		status = parse_pipeline_elem(pipeline, tokenizer);
		if (status != PARSING_SUCCEEDED)
			return (status);
		status = match_token(tokenizer, "|", NULL);
		if (status == PARSING_FAILED)
			return (PARSING_SUCCEEDED);
		if (status != PARSING_SUCCEEDED)
			return (status);
		status = parse_linebreak(tokenizer, "pipe> ");
		if (status != PARSING_SUCCEEDED)
			return (status);
	}
	return (PARSING_SUCCEEDED);
}

void	free_pipeline(t_pipeline pipeline)
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
