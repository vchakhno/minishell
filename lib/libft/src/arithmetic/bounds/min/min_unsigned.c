/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_unsigned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:20:48 by vchakhno          #+#    #+#             */
/*   Updated: 2023/05/18 07:20:21 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/arithmetic/bounds.h"

t_u8	ft_u8_min(t_u8 a, t_u8 b)
{
	if (a < b)
		return (a);
	return (b);
}

t_u16	ft_u16_min(t_u16 a, t_u16 b)
{
	if (a < b)
		return (a);
	return (b);
}

t_u32	ft_u32_min(t_u32 a, t_u32 b)
{
	if (a < b)
		return (a);
	return (b);
}

t_u64	ft_u64_min(t_u64 a, t_u64 b)
{
	if (a < b)
		return (a);
	return (b);
}
