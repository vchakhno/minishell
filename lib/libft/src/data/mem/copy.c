/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 05:41:15 by vchakhno          #+#    #+#             */
/*   Updated: 2023/06/03 20:47:49 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/mem.h"

void	ft_mem_copy(t_mem *dest, const t_mem *src, t_u32 size)
{
	const t_byte	*src_bytes = src;
	t_byte *const	dest_bytes = dest;
	t_u32			i;

	if (src == dest)
		return ;
	i = 0;
	while (i < size)
	{
		dest_bytes[i] = src_bytes[i];
		i++;
	}
}
