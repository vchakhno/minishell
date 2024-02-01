/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 22:29:30 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 02:38:55 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/array.h"
#include "libft/data/mem.h"

bool	_ft_array_compare_elems(t_array array,
			t_comparison_func func, t_u32 i, t_u32 j);

static t_u32	ft_array_quicksort_partition(
	t_array array, t_comparison_func func, t_u32 low, t_u32 high
) {
	t_u32	insertion_index;
	t_u32	i;

	insertion_index = low;
	i = low;
	while (i < high)
	{
		if (!_ft_array_compare_elems(array, func, i, high))
		{
			ft_mem_swap(
				ft_array_at(array, i), ft_array_at(array, insertion_index),
				array.elem_size);
			insertion_index++;
		}
		i++;
	}
	ft_mem_swap(
		ft_array_at(array, i), ft_array_at(array, insertion_index),
		array.elem_size);
	return (insertion_index);
}

static void	ft_array_quicksort(
	t_array array, t_comparison_func func, t_i32 low, t_i32 high
) {
	t_u32	pivot_index;

	if (low >= high)
		return ;
	pivot_index = ft_array_quicksort_partition(array, func, low, high);
	ft_array_quicksort(array, func, low, pivot_index - 1);
	ft_array_quicksort(array, func, pivot_index + 1, high);
}

void	ft_array_sort(t_array array, t_comparison_func func)
{
	ft_array_quicksort(array, func, 0, array.size - 1);
}
