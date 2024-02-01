/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capacity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 08:10:29 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 09:35:06 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/vector.h"
#include "libft/data/mem.h"
#include "libft/arithmetic/bounds.h"
#include <stdlib.h>

bool	ft_vector_reserve(t_vector *vec, t_u32 additionnal)
{
	t_u32	new_capacity;
	void	*new_elems;

	if (vec->size + additionnal <= vec->capacity)
		return (true);
	new_capacity = ft_u32_max(
			vec->size + additionnal,
			vec->capacity * LIBFT_VECTOR_GROWTH_FACTOR);
	if (!ft_mem_malloc(&new_elems, new_capacity * vec->elem_size))
		return (false);
	ft_mem_copy(new_elems, vec->elems, vec->size * vec->elem_size);
	free(vec->elems);
	vec->elems = new_elems;
	vec->capacity = new_capacity;
	return (true);
}

bool	ft_vector_reserve_exact(t_vector *vec, t_u32 additionnal)
{
	void	*new_elems;

	if (vec->size + additionnal <= vec->capacity)
		return (true);
	if (!ft_mem_malloc(&new_elems, (vec->size + additionnal) * vec->elem_size))
		return (false);
	ft_mem_copy(new_elems, vec->elems, vec->size * vec->elem_size);
	free(vec->elems);
	vec->elems = new_elems;
	vec->capacity = vec->size + additionnal;
	return (true);
}

bool	ft_vector_compact(t_vector *vec)
{
	void	*new_elems;

	if (vec->capacity == vec->size)
		return (true);
	if (!ft_mem_dup(&new_elems, vec->elems, vec->size * vec->elem_size))
		return (false);
	free(vec->elems);
	vec->elems = new_elems;
	vec->capacity = vec->size;
	return (true);
}
