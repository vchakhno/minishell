/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_get_slice.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:00:39 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 04:49:39 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/str.h"
#include "libft/arithmetic/bounds.h"

t_str	ft_str_get_slice__unchecked(t_str str, t_u32 start, t_u32 len)
{
	t_str	slice;

	slice.c_str = str.c_str + start;
	slice.len = len;
	return (slice);
}

t_str	ft_str_get_slice(t_str str, t_u32 start, t_u32 len)
{
	t_str	slice;

	start = ft_u32_min(start, str.len);
	slice.c_str = str.c_str + start;
	slice.len = ft_u32_min(len, str.len - start);
	return (slice);
}
