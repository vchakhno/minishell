/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 23:54:15 by vchakhno          #+#    #+#             */
/*   Updated: 2023/09/16 00:08:29 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/mem.h"

bool	ft_mem_dup(t_ptr *ptr, t_mem *src, t_u32 size)
{
	if (!ft_mem_malloc(ptr, size))
		return (false);
	ft_mem_copy(*(t_byte **) ptr, src, size);
	return (true);
}
