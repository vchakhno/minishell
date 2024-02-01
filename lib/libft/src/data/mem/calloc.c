/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 05:38:11 by vchakhno          #+#    #+#             */
/*   Updated: 2023/06/03 20:47:49 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/mem.h"

bool	ft_mem_calloc(t_ptr *ptr, t_u32 count, t_u32 size)
{
	if (size != 0 && count > (t_u32)(-1) / size)
		return (false);
	if (ft_mem_malloc(ptr, count * size))
		ft_mem_zero(*(void **)ptr, count * size);
	return (*(void **)ptr);
}
