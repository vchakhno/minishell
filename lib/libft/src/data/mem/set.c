/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 05:41:32 by vchakhno          #+#    #+#             */
/*   Updated: 2023/06/03 20:47:49 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/mem.h"

void	ft_mem_set(t_mem *mem, t_u32 size, t_byte b)
{
	t_byte *const	bytes = mem;
	t_u32			i;

	i = 0;
	while (i < size)
	{
		bytes[i] = b;
		i++;
	}
}
