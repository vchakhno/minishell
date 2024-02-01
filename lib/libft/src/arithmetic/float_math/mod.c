/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 01:04:24 by vchakhno          #+#    #+#             */
/*   Updated: 2023/05/18 07:20:48 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/arithmetic/float_math.h"

t_f32	ft_f32_mod(t_f32 value, t_f32 mod)
{
	return (value - ft_f32_trunc(value / mod) * mod);
}

t_f64	ft_f64_mod(t_f64 value, t_f64 mod)
{
	return (value - ft_f64_trunc(value / mod) * mod);
}

t_f80	ft_f80_mod(t_f80 value, t_f80 mod)
{
	return (value - ft_f80_trunc(value / mod) * mod);
}

t_f128	ft_f128_mod(t_f128 value, t_f128 mod)
{
	return (value - ft_f128_trunc(value / mod) * mod);
}
