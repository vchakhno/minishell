/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trunc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 01:08:15 by vchakhno          #+#    #+#             */
/*   Updated: 2023/05/18 07:21:09 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/arithmetic/float_math.h"

// Bounds are ]-2^23, 2^23[
t_f32	ft_f32_trunc(t_f32 value)
{
	if (value <= -8388608.f || 8388608.f <= value)
		return (value);
	return ((t_i32)value);
}

// Bounds are ]-2^52, 2^52[
t_f64	ft_f64_trunc(t_f64 value)
{
	if (value <= -4503599627370496. || 4503599627370496. <= value)
		return (value);
	return ((t_i64)value);
}

t_f80	ft_f80_trunc(t_f80 value)
{
	if (value <= -9223372036854775808.l || 9223372036854775808.l <= value)
		return (value);
	return ((t_i64)value);
}

t_f128	ft_f128_trunc(t_f128 value)
{
	t_i16	exponent;
	t_i16	shift;

	exponent = (((t_i16 *)&value)[7] & 0x7FFF) - 0x3FFF;
	if (exponent > 112)
		return (value);
	if (exponent < 0)
		return (0);
	shift = 112 - exponent;
	if (shift < 64)
	{
		*(uint64_t *)&value = *(uint64_t *)&value >> shift << shift;
	}
	else
	{
		*(uint64_t *)&value = 0;
		((uint64_t *)&value)[1] = ((uint64_t *)&value)[1] >> shift << shift;
	}
	return (value);
}
