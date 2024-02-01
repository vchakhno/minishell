/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 08:56:23 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

t_parsing_status	parse_pipeline_elem_parens(
	t_pipeline *pipeline, t_pipeline_elem *elem, t_tokenizer *tokenizer,
	t_u8 *exit_status
) {
	t_parsing_status	status;

	elem->kind = PARENS_ELEM;
	if (!alloc_and_or(&elem->parens))
		return (PARSING_CANCELED);
	status = parse_and_or(&elem->parens, tokenizer, exit_status);
	if (status != PARSING_SUCCEEDED)
	{
		free_and_or(elem->parens);
		return (status);
	}
	if (!ft_vector_push(pipeline, elem))
	{
		free_and_or(elem->parens);
		return (PARSING_CANCELED);
	}
	status = match_token(tokenizer, ")", NULL, exit_status);
	if (status != PARSING_SUCCEEDED)
	{
		free_and_or(elem->parens);
		return (status);
	}
	return (PARSING_SUCCEEDED);
}

t_parsing_status	parse_pipeline_elem_cmd(
	t_pipeline *pipeline, t_pipeline_elem *elem, t_tokenizer *tokenizer,
	t_u8 *exit_status
) {
	t_parsing_status	status;

	elem->kind = CMD_ELEM;
	if (!alloc_simple_command(&elem->simple_command))
		return (PARSING_CANCELED);
	status = parse_simple_command(&elem->simple_command, tokenizer,
			exit_status);
	if (status != PARSING_SUCCEEDED)
	{
		free_simple_command(elem->simple_command);
		return (status);
	}
	if (!ft_vector_push(pipeline, elem))
	{
		free_simple_command(elem->simple_command);
		return (PARSING_CANCELED);
	}
	return (PARSING_SUCCEEDED);
}

t_parsing_status	parse_pipeline_elem(
	t_pipeline *pipeline, t_tokenizer *tokenizer, t_u8 *exit_status
) {
	t_pipeline_elem		elem;
	t_parsing_status	status;

	status = match_token(tokenizer, "(", NULL, exit_status);
	if (status == PARSING_SUCCEEDED)
		return (parse_pipeline_elem_parens(pipeline, &elem, tokenizer,
				exit_status));
	else if (status == PARSING_FAILED)
		return (parse_pipeline_elem_cmd(pipeline, &elem, tokenizer,
				exit_status));
	return (status);
}

bool	run_pipeline_elem(t_pipeline_elem elem, t_runtime_context *context)
{
	if (elem.kind == CMD_ELEM)
		return (run_simple_command(elem.simple_command, context));
	else
		return (run_and_or(elem.parens, context));
}

void	free_pipeline_elem(t_pipeline_elem elem)
{
	if (elem.kind == CMD_ELEM)
		free_simple_command(elem.simple_command);
	else
		free_and_or(elem.parens);
}
