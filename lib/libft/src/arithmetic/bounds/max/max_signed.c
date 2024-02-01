/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_signed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:20:48 by vchakhno          #+#    #+#             */
/*   Updated: 2023/05/18 07:20:21 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/arithmetic/bounds.h"

t_i8	ft_i8_max(t_i8 a, t_i8 b)
{
	if (a > b)
		return (a);
	return (b);
}

t_i16	ft_i16_max(t_i16 a, t_i16 b)
{
	if (a > b)
		return (a);
	return (b);
}

t_i32	ft_i32_max(t_i32 a, t_i32 b)
{
	if (a > b)
		return (a);
	return (b);
}

t_i64	ft_i64_max(t_i64 a, t_i64 b)
{
	if (a > b)
		return (a);
	return (b);
}
