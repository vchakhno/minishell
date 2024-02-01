/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_byte.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 05:38:22 by vchakhno          #+#    #+#             */
/*   Updated: 2023/06/03 20:47:49 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/mem.h"

bool	ft_mem_find_byte(const t_mem *mem, t_u32 size, t_byte b, t_u32 *index)
{
	const t_byte	*bytes = mem;
	t_u32			i;

	i = 0;
	while (i < size)
	{
		if (bytes[i] == b)
		{
			*index = i;
			return (true);
		}
		i++;
	}
	return (false);
}
