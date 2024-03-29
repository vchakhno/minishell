/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 08:49:42 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

bool	alloc_pipeline(t_pipeline *pipeline)
{
	if (!ft_vector_alloc(pipeline, sizeof(t_pipeline_elem), 8))
		return (false);
	return (true);
}

t_parsing_status	parse_pipeline(
	t_pipeline *pipeline, t_tokenizer *tokenizer, t_u8 *exit_status
) {
	t_parsing_status	status;

	while (true)
	{
		status = parse_pipeline_elem(pipeline, tokenizer, exit_status);
		if (status != PARSING_SUCCEEDED)
			return (status);
		status = match_token(tokenizer, "|", NULL, exit_status);
		if (status == PARSING_FAILED)
			return (PARSING_SUCCEEDED);
		if (status != PARSING_SUCCEEDED)
			return (status);
		status = parse_linebreak(tokenizer, "pipe> ", exit_status);
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
		free_pipeline_elem(((t_pipeline_elem *)pipeline.elems)[i]);
		i++;
	}
	ft_vector_free(pipeline);
}
