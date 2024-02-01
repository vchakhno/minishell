/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 00:05:13 by vchakhno          #+#    #+#             */
/*   Updated: 2023/08/31 20:24:50 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/input.h"
#include "libft/data/mem.h"
#include <stdio.h>
#include "libft/arithmetic/bounds.h"

void	ft_buf_input_init(
	t_buf_input *input, void *buffer, t_u32 buffer_size, t_input *source
) {
	ft_input_init(&input->input, ft_buf_input_read_upto);
	input->buffer = buffer;
	input->capacity = buffer_size;
	input->pos = 0;
	input->size = 0;
	input->source = source;
}

bool	ft_buf_input_read_upto(
	t_buf_input *input, void *ptr, t_u32 max_size, t_u32 *out_size
) {
	if (input->pos + max_size <= input->size)
	{
		ft_buf_input_read_upto__from_buf(input, ptr, max_size, out_size);
		return (true);
	}
	return (
		ft_buf_input_read_upto__from_source(input, ptr, max_size, out_size)
	);
}

void	ft_buf_input_read_upto__from_buf(
	t_buf_input *input, void *ptr, t_u32 max_size, t_u32 *out_size
) {
	ft_mem_copy(ptr, input->buffer + input->pos, max_size);
	if (input->pos + max_size == input->size)
	{
		input->pos = 0;
		input->size = 0;
	}
	else
	{
		input->pos += max_size;
	}
	*out_size = max_size;
}

bool	ft_buf_input_read_upto__from_source(
	t_buf_input *input, void *ptr, t_u32 max_size, t_u32 *out_size
) {
	t_u32	copy_size;
	t_u32	read_size;

	copy_size = input->size - input->pos;
	ft_mem_copy(ptr, input->buffer + input->pos, copy_size);
	if (input->pos + max_size < input->size + input->capacity)
	{
		if (!ft_input_read_upto(input->source,
				input->buffer, input->capacity, &input->size))
			return (false);
		input->pos = ft_u32_min(max_size - copy_size, input->size);
		ft_mem_copy(ptr + copy_size, input->buffer, input->pos);
		*out_size = copy_size + input->pos;
	}
	else
	{
		input->pos = 0;
		input->size = 0;
		if (!ft_input_read_upto(input->source,
				ptr + copy_size, max_size - copy_size, &read_size))
			return (false);
		*out_size = copy_size + read_size;
	}
	return (true);
}
