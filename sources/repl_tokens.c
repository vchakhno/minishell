/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:55:05 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/01 01:32:17 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	alloc_repl_tokens(t_repl_tokens *tokens)
{
	if (!ft_vector_alloc(&tokens->tokens, 30))
		return (false);
	tokens->pos = 0;
	return (true);
}

bool	wait_repl_tokens(t_repl_tokens *tokens)
{
	bool	end;

	if (!tokenize_line())
		return (false);
	return (true);
}

void	free_repl_tokens(t_repl_tokens tokens)
{
	ft_vector_free(tokens.tokens);
}
