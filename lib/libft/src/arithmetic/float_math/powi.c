/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 01:05:17 by vchakhno          #+#    #+#             */
/*   Updated: 2023/06/29 05:56:14 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/arithmetic/float_math.h"

t_f32	ft_f32_powi(t_f32 base, t_i32 exponent)
{
	t_f32	value;

	value = 1;
	if (exponent < 0)
	{
		while (exponent)
		{
			value /= base;
			exponent++;
		}
	}
	else
	{
		while (exponent)
		{
			value *= base;
			exponent--;
		}
	}
	return (value);
}

t_f64	ft_f64_powi(t_f64 base, t_i32 exponent)
{
	t_f64	value;

	value = 1;
	if (exponent < 0)
	{
		while (exponent)
		{
			value /= base;
			exponent++;
		}
	}
	else
	{
		while (exponent)
		{
			value *= base;
			exponent--;
		}
	}
	return (value);
}

t_f80	ft_f80_powi(t_f80 base, t_i32 exponent)
{
	t_f80	value;

	value = 1;
	if (exponent < 0)
	{
		while (exponent)
		{
			value /= base;
			exponent++;
		}
	}
	else
	{
		while (exponent)
		{
			value *= base;
			exponent--;
		}
	}
	return (value);
}

t_f128	ft_f128_powi(t_f128 base, t_i32 exponent)
{
	t_f128	value;

	value = 1;
	if (exponent < 0)
	{
		while (exponent)
		{
			value /= base;
			exponent++;
		}
	}
	else
	{
		while (exponent)
		{
			value *= base;
			exponent--;
		}
	}
	return (value);
}
