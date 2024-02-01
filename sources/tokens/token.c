/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:48:18 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 01:47:54 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_str	get_token_content(t_shell_input input, t_token token)
{
	return (ft_str_get_slice(input.text.str, token.start, token.len));
}

void	print_token(t_shell_input input, t_token token)
{
	ft_println("({c_str}, \"{str}\")",
		(char *[]){"OP", "WORD"}[token.type], get_token_content(input, token));
}
