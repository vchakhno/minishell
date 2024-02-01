/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:38:25 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 13:59:37 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/input.h"
#include "libft/data/str.h"
#include <stddef.h>

void	ft_input_init(t_input *input, t_input_read_upto read_upto)
{
	input->read_upto = read_upto;
	input->ended = false;
}

bool	ft_input_has_ended(t_input *input)
{
	return (input->ended);
}

bool	ft_input_read(t_input *input, void *ptr, t_u32 size)
{
	t_u32	total_read;
	t_u32	last_read;

	total_read = 0;
	while (total_read < size)
	{
		if (!ft_input_read_upto(input, ptr, size - total_read, &last_read))
			return (false);
		total_read += last_read;
	}
	return (true);
}

bool	ft_input_read_upto(
	t_input *input, void *ptr, t_u32 capacity, t_u32 *out_size
) {
	if (!input->read_upto(input, ptr, capacity, out_size))
	{
		input->ended = true;
		return (false);
	}
	return (true);
}

bool	ft_input_read_byte(t_input *input, t_u8 *byte)
{
	return (ft_input_read(input, byte, 1));
}
