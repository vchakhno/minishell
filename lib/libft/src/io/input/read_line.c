/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:57:40 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/20 04:35:58 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/input.h"

bool	ft_input_read_line(t_input *input, t_string *line)
{
	t_u8	byte;
	bool	first;

	first = true;
	if (!ft_string_alloc(line, 8))
		return (false);
	while (ft_input_read_byte(input, &byte))
	{
		first = false;
		if (!ft_string_append_str(line, (t_str){(char *)&byte, 1}))
		{
			ft_string_free(*line);
			return (false);
		}
		if (byte == '\n')
			return (true);
	}
	return (!first);
}
