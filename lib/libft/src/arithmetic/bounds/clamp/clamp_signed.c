/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp_signed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:20:48 by vchakhno          #+#    #+#             */
/*   Updated: 2023/06/03 20:51:30 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/arithmetic/bounds.h"

t_i8	ft_i8_clamp(t_i8 min, t_i8 value, t_i8 max)
{
	return (ft_i8_min(ft_i8_max(min, value), max));
}

t_i16	ft_i16_clamp(t_i16 min, t_i16 value, t_i16 max)
{
	return (ft_i16_min(ft_i16_max(min, value), max));
}

t_i32	ft_i32_clamp(t_i32 min, t_i32 value, t_i32 max)
{
	return (ft_i32_min(ft_i32_max(min, value), max));
}

t_i64	ft_i64_clamp(t_i64 min, t_i64 value, t_i64 max)
{
	return (ft_i64_min(ft_i64_max(min, value), max));
}
