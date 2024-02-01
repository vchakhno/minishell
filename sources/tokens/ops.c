/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:48:18 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 01:47:32 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool	check_ops(t_shell_input input, t_u32 *len)
{
	char *const	ops[] = {
		"<<", "<", ">>", ">", "&&", "||", "|", "(", ")", "\n"
	};
	t_str		lines_str;
	t_u32		i;

	lines_str.c_str = input.text.c_str + input.cursor;
	lines_str.len = input.text.len - input.cursor;
	i = 0;
	while (i < (int) sizeof ops / sizeof * ops)
	{
		if (ft_str_starts_with_c_str(lines_str, ops[i]))
		{
			if (len)
				*len = ft_c_str_len(ops[i]);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	match_ops(t_shell_input *input, t_token *token)
{
	if (check_ops(*input, &token->len))
	{
		token->type = TOKEN_OP;
		input->cursor += token->len;
		return (true);
	}
	return (false);
}
