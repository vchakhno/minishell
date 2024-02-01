/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libuf_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:32:15 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 03:52:50 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/output.h"
#include "libft/data/mem.h"
#include "libft/data/str.h"

void	ft_libuf_output_init(
	t_libuf_output *output, void *buffer, t_u32 buffer_size, t_output *dest
) {
	ft_output_init(&output->output, ft_libuf_output_write);
	output->buffer = buffer;
	output->capacity = buffer_size;
	output->pos = 0;
	output->dest = dest;
}

bool	ft_libuf_output_write(t_libuf_output *output, void *ptr, t_u32 size)
{
	if (!ft_str_contains_char((t_str){ptr, size}, '\n'))
		return (ft_buf_output_write(output, ptr, size));
	if (size <= output->capacity - output->pos)
	{
		ft_mem_copy(output->buffer + output->pos, ptr, size);
		output->pos += size;
	}
	if (!ft_libuf_output_flush(output))
		return (false);
	if (size > output->capacity - output->pos
		&& !ft_output_write(output->dest, ptr, size))
		return (false);
	return (true);
}

bool	ft_libuf_output_flush(t_libuf_output *output)
{
	return (ft_buf_output_flush(output));
}
