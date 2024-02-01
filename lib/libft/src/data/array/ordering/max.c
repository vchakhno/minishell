/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:47:08 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 02:36:57 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/array.h"
#include "libft/data/mem.h"
#include "libft/arithmetic/fixed_types.h"

bool	_ft_array_compare_elems(t_array array,
			t_comparison_func func, t_u32 i, t_u32 j);

bool	ft_array_max(t_array array, t_comparison_func func, void *dest)
{
	t_u32	i;
	t_u32	max_index;

	if (array.size == 0)
		return (false);
	max_index = 0;
	i = 1;
	while (i < array.size)
	{
		if (_ft_array_compare_elems(array, func, i, max_index))
			max_index = i;
		i++;
	}
	ft_mem_copy(dest, ft_array_at(array, max_index), array.elem_size);
	return (true);
}
