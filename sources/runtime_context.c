/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime_context.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:38:29 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 04:01:29 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime_context.h"
#include "grammar.h"

bool	alloc_runtime_context(t_runtime_context *context, char **env)
{
	if (!parse_env(&context->env, env))
		return (false);
	context->exit_status = 0;
	return (true);
}

void	free_runtime_context(t_runtime_context context)
{
	free_env(context.env);
}
