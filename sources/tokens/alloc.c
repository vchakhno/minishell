/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:48:18 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 01:48:14 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool	alloc_tokenizer(t_tokenizer *tokenizer, t_shell_input *input)
{
	if (!ft_vector_alloc(&tokenizer->tokens, sizeof(t_token), 30))
		return (false);
	tokenizer->input = input;
	return (true);
}

void	free_tokenizer(t_tokenizer tokenizer)
{
	ft_vector_free(tokenizer.tokens);
}
