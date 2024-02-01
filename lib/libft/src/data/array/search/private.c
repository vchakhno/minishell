/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 08:21:06 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 02:32:40 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/array.h"
#include "libft/data/mem.h"

bool	_ft_array_elem_equal(
	t_array array, t_u32 i, void *data, t_equality_func func
) {
	void	*elem;

	elem = ft_array_at(array, i);
	if (!func)
		return (ft_mem_equal(elem, data, array.elem_size));
	return (func(elem, data));
}
