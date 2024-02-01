/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:02:39 by vchakhno          #+#    #+#             */
/*   Updated: 2023/06/03 20:47:49 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/mem.h"

void	ft_mem_swap(t_mem *mem1, t_mem *mem2, t_u32 n)
{
	t_byte *const	bytes1 = mem1;
	t_byte *const	bytes2 = mem2;
	t_u32			i;
	t_byte			t;

	i = 0;
	while (i < n)
	{
		t = bytes1[i];
		bytes1[i] = bytes2[i];
		bytes2[i] = t;
		i++;
	}
}
