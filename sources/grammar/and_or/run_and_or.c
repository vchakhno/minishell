/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_and_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 11:48:08 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

bool	run_and_or(t_and_or and_or, t_runtime_context *context)
{
	t_and_or_elem	elem;
	t_u32			i;

	if (!run_pipeline(((t_and_or_elem *)and_or.elems)[0].pipeline, context))
		return (false);
	i = 1;
	while (i < and_or.size)
	{
		elem = ((t_and_or_elem *)and_or.elems)[i];
		if ((context->exit_status == 0) == (elem.kind == AND_ELEM)
			&& !run_pipeline(elem.pipeline, context))
			return (false);
		i++;
	}
	return (true);
}
