/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:32:15 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 03:52:50 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/output.h"
#include "libft/data/mem.h"
#include "libft/arithmetic/bounds.h"

void	ft_buf_output_init(
	t_buf_output *output, void *buffer, t_u32 buffer_size, t_output *dest
) {
	ft_output_init(&output->output, ft_buf_output_write);
	output->buffer = buffer;
	output->capacity = buffer_size;
	output->pos = 0;
	output->dest = dest;
}

bool	ft_buf_output_write(t_buf_output *output, void *ptr, t_u32 size)
{
	t_u32	written;

	if (output->pos + size < output->capacity)
	{
		ft_mem_copy(output->buffer + output->pos, ptr, size);
		output->pos += size;
	}
	else if (output->pos + size < 2 * output->capacity)
	{
		written = output->capacity - output->pos;
		ft_mem_copy(output->buffer + output->pos, ptr, written);
		if (!ft_output_write(output->dest,
				output->buffer, output->capacity))
			return (false);
		ft_mem_copy(output->buffer, ptr + written, size - written);
		output->pos = size - written;
	}
	else if (!ft_buf_output_flush(output)
		|| !ft_output_write(output->dest, ptr, size))
		return (false);
	return (true);
}

bool	ft_buf_output_flush(t_buf_output *output)
{
	if (!ft_output_write(output->dest, output->buffer, output->pos))
		return (false);
	output->pos = 0;
	return (true);
}
