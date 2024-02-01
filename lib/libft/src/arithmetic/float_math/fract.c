/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 01:05:17 by vchakhno          #+#    #+#             */
/*   Updated: 2023/05/18 07:20:48 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/arithmetic/float_math.h"

t_f32	ft_f32_fract(t_f32 value)
{
	return (value - ft_f32_trunc(value));
}

t_f64	ft_f64_fract(t_f64 value)
{
	return (value - ft_f64_trunc(value));
}

t_f80	ft_f80_fract(t_f80 value)
{
	return (value - ft_f80_trunc(value));
}

t_f128	ft_f128_fract(t_f128 value)
{
	return (value - ft_f128_trunc(value));
}
