/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:20:48 by vchakhno          #+#    #+#             */
/*   Updated: 2023/05/31 08:27:22 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/arithmetic/bounds.h"

t_u8	ft_u8_clamp(t_u8 min, t_u8 value, t_u8 max)
{
	return (ft_u8_min(ft_u8_max(min, value), max));
}

t_u16	ft_u16_clamp(t_u16 min, t_u16 value, t_u16 max)
{
	return (ft_u16_min(ft_u16_max(min, value), max));
}

t_u32	ft_u32_clamp(t_u32 min, t_u32 value, t_u32 max)
{
	return (ft_u32_min(ft_u32_max(min, value), max));
}

t_u64	ft_u64_clamp(t_u64 min, t_u64 value, t_u64 max)
{
	return (ft_u64_min(ft_u64_max(min, value), max));
}
