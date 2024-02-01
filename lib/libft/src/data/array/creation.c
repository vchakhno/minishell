/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   borrowing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:58:46 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 01:49:53 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/array.h"
#include "libft/arithmetic/bounds.h"

t_array	ft_array_from(void *elems, t_u32 elem_size, t_u32 size)
{
	t_array	array;

	array.elems = elems;
	array.size = size;
	array.elem_size = elem_size;
	return (array);
}

t_array	array_get_slice__unchecked(t_array array, t_u32 start, t_u32 len)
{
	t_array	slice;

	slice.elems = ft_array_at(array, start);
	slice.size = len;
	slice.elem_size = array.elem_size;
	return (slice);
}

t_array	array_get_slice(
	t_array array, t_u32 start, t_u32 len
) {
	t_array	slice;

	start = ft_u32_min(start, array.size);
	slice.elems = ft_array_at(array, start);
	slice.size = ft_u32_min(len, array.size - start);
	slice.elem_size = array.elem_size;
	return (slice);
}
