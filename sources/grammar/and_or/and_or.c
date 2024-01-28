/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 10:52:17 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

bool	alloc_and_or(t_vector *and_or)
{
	if (!ft_vector_alloc(and_or, sizeof(t_and_or_elem), 8))
		return (false);
	return (true);
}

t_parsing_status	parse_and_or_elem(
	t_vector *and_or, t_tokenizer *tokenizer, t_and_or_elem_kind kind
) {
	t_and_or_elem		elem;
	t_parsing_status	status;

	if (!alloc_pipeline(&elem.pipeline))
		return (PARSING_CANCELED);
	status = parse_pipeline(&elem.pipeline, tokenizer);
	if (status != PARSING_SUCCEEDED)
	{
		free_pipeline(elem.pipeline);
		return (status);
	}
	elem.kind = kind;
	if (!ft_vector_push(and_or, &elem))
	{
		free_pipeline(elem.pipeline);
		return (PARSING_CANCELED);
	}
	return (PARSING_SUCCEEDED);
}

t_parsing_status	parse_and_or_separator(
	t_and_or_elem_kind *kind, t_tokenizer *tokenizer
) {
	t_parsing_status	status;

	status = match_token(tokenizer, "&&", NULL);
	if (status == PARSING_SUCCEEDED)
		*kind = AND_ELEM;
	if (status != PARSING_FAILED)
		return (status);
	status = match_token(tokenizer, "||", NULL);
	if (status == PARSING_SUCCEEDED)
		*kind = OR_ELEM;
	return (status);
}

t_parsing_status	parse_and_or(t_vector *and_or, t_tokenizer *tokenizer)
{
	t_parsing_status	status;
	t_and_or_elem_kind	kind;

	kind = AND_ELEM;
	while (true)
	{
		status = parse_and_or_elem(and_or, tokenizer, kind);
		if (status != PARSING_SUCCEEDED)
			return (status);
		status = parse_and_or_separator(&kind, tokenizer);
		if (status == PARSING_FAILED)
			return (PARSING_SUCCEEDED);
		if (status != PARSING_SUCCEEDED)
			return (status);
		status = parse_linebreak(tokenizer, &"and> \0or> "[6 * kind]);
		if (status != PARSING_SUCCEEDED)
			return (status);
	}
	return (PARSING_SUCCEEDED);
}

void	free_and_or(t_vector and_or)
{
	t_u32	i;

	i = 0;
	while (i < and_or.size)
	{
		free_pipeline(((t_and_or_elem *)and_or.elems)[i].pipeline);
		i++;
	}
	ft_vector_free(and_or);
}
