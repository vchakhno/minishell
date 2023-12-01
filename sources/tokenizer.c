/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:48:18 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/01 01:26:57 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	tokenize(t_str line)
{
	t_vector	tokens;
	t_str		cropped;
	t_u32		i;

	if (!ft_vector_alloc(&tokens, sizeof(t_token), 32))
		return (false);
	i = 0;
	while (i < line.len)
	{
		cropped = ft_str_get_slice(line, i, line.len - i);
		i++;
	}
	return (true);
}
