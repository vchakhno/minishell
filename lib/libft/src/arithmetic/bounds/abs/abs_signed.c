/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs_signed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:46:22 by vchakhno          #+#    #+#             */
/*   Updated: 2023/05/18 07:20:21 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/arithmetic/bounds.h"

t_u8	ft_i8_abs(t_i8 value)
{
	if (value < 0)
		return (-value);
	return (value);
}

t_u16	ft_i16_abs(t_i16 value)
{
	if (value < 0)
		return (-value);
	return (value);
}

t_u32	ft_i32_abs(t_i32 value)
{
	if (value < 0)
		return (-value);
	return (value);
}

t_u64	ft_i64_abs(t_i64 value)
{
	if (value < 0)
		return (-value);
	return (value);
}
