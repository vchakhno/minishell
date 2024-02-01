/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 03:56:30 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 10:20:28 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/vector.h"
#include "libft/data/mem.h"
#include <stdlib.h>

bool	ft_vector_alloc(t_vector *vec, t_u32 elem_size, t_u32 capacity)
{
	if (!ft_mem_malloc(&vec->elems, elem_size * capacity))
		return (false);
	vec->elem_size = elem_size;
	vec->size = 0;
	vec->capacity = capacity;
	return (true);
}

void	ft_vector_free(t_vector vec)
{
	free(vec.elems);
}
