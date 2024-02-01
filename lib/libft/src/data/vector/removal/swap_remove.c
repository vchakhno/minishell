/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:03:20 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 02:46:25 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/vector.h"
#include "libft/data/array.h"
#include "libft/data/mem.h"
#include "libft/arithmetic/bounds.h"

bool	ft_vector_swap_remove(t_vector *vec, t_u32 i, void *dest)
{
	return (ft_vector_swap_remove_multiple(vec, i, dest, 1));
}

t_u32	ft_vector_swap_remove_multiple(
	t_vector *vec, t_u32 i, void *dest, t_u32 count
) {
	count = ft_u32_min(count, vec->size - i);
	if (dest)
	{
		ft_mem_copy(dest, ft_array_at(vec->array, i), count * vec->elem_size);
	}
	ft_mem_copy(ft_array_at(vec->array, i), ft_array_at(vec->array, i + count),
		ft_u32_min(count, vec->size - i - count));
	vec->size -= count;
	return (count);
}
