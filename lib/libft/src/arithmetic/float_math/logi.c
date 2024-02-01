/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 01:08:15 by vchakhno          #+#    #+#             */
/*   Updated: 2023/06/29 08:10:23 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/arithmetic/float_math.h"
#include "libft/arithmetic/bounds.h"

t_i32	ft_f32_logi(t_f32 value, t_f32 base)
{
	t_i32	i;

	if (value <= 0 || base <= 1)
		return (0);
	i = 0;
	if (value >= base)
	{
		while (value >= base)
		{
			value /= base;
			i++;
		}
	}
	else if (value < 1)
	{
		while (value < 1)
		{
			value *= base;
			i--;
		}
	}
	return (i);
}

t_i32	ft_f64_logi(t_f64 value, t_f64 base)
{
	t_i32	i;

	if (value <= 0 || base <= 1)
		return (0);
	i = 0;
	if (value >= base)
	{
		while (value >= base)
		{
			value /= base;
			i++;
		}
	}
	else if (value < 1)
	{
		while (value < 1)
		{
			value *= base;
			i--;
		}
	}
	return (i);
}

t_i32	ft_f80_logi(t_f80 value, t_f80 base)
{
	t_i32	i;

	if (value <= 0 || base <= 1)
		return (0);
	i = 0;
	if (value >= base)
	{
		while (value >= base)
		{
			value /= base;
			i++;
		}
	}
	else if (value < 1)
	{
		while (value < 1)
		{
			value *= base;
			i--;
		}
	}
	return (i);
}

t_i32	ft_f128_logi(t_f128 value, t_f128 base)
{
	t_i32	i;

	if (value <= 0 || base <= 1)
		return (0);
	i = 0;
	if (value >= base)
	{
		while (value >= base)
		{
			value /= base;
			i++;
		}
	}
	else if (value < 1)
	{
		while (value < 1)
		{
			value *= base;
			i--;
		}
	}
	return (i);
}
