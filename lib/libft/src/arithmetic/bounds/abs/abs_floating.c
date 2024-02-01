/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs_floating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:46:22 by vchakhno          #+#    #+#             */
/*   Updated: 2023/05/18 07:20:21 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/arithmetic/bounds.h"

t_f32	ft_f32_abs(t_f32 value)
{
	if (value < 0)
		return (-value);
	return (value);
}

t_f64	ft_f64_abs(t_f64 value)
{
	if (value < 0)
		return (-value);
	return (value);
}

t_f80	ft_f80_abs(t_f80 value)
{
	if (value < 0)
		return (-value);
	return (value);
}

t_f128	ft_f128_abs(t_f128 value)
{
	if (value < 0)
		return (-value);
	return (value);
}
