/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:01:53 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 09:35:27 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/vector.h"
#include "libft/arithmetic/bounds.h"
#include "libft/data/mem.h"
#include <stdlib.h>

bool	ft_vector_insert(t_vector *vec, t_u32 index, void *value)
{
	return (ft_vector_insert_multiple(vec, index, value, 1));
}

bool	ft_vector_insert_multiple(
	t_vector *vec, t_u32 i, void *values, t_u32 count
) {
	void	*new_elems;
	t_u32	new_capacity;

	if (vec->size + count <= vec->capacity)
		ft_mem_move(vec->elems + (i + count) * vec->elem_size,
			vec->elems + i * vec->elem_size,
			(vec->size - i) * vec->elem_size);
	else
	{
		new_capacity = ft_u32_max(
				vec->size + count,
				vec->capacity * LIBFT_VECTOR_GROWTH_FACTOR);
		if (!ft_mem_malloc(&new_elems, new_capacity * vec->elem_size))
			return (false);
		ft_mem_copy(new_elems, vec->elems, i * vec->elem_size);
		ft_mem_copy(new_elems + (i + count) * vec->elem_size,
			vec->elems + i * vec->elem_size,
			(vec->size - i) * vec->elem_size);
		free(vec->elems);
		vec->elems = new_elems;
		vec->capacity = new_capacity;
	}
	ft_mem_copy(ft_array_at(vec->array, i), values, count * vec->elem_size);
	vec->size += count;
	return (true);
}
