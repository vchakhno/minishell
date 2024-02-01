/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:53:45 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/22 23:50:03 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printing.h"
#include "libft/arithmetic/bounds.h"
#include "libft/io/printf.h"

bool	ft_i8_oprint(t_i8 value, t_output *output)
{
	if (value < 0)
	{
		if (!ft_output_write(output, "-", 1))
			return (false);
	}
	if (value / 10)
	{
		if (!ft_i8_oprint(ft_i8_abs(value / 10), output))
			return (false);
	}
	return (
		ft_output_write(output, &(char){ft_i8_abs(value % 10) + '0'}, 1)
	);
}

bool	ft_i16_oprint(t_i16 value, t_output *output)
{
	if (value < 0)
	{
		if (!ft_output_write(output, "-", 1))
			return (false);
	}
	if (value / 10)
	{
		if (!ft_i16_oprint(ft_i16_abs(value / 10), output))
			return (false);
	}
	return (
		ft_output_write(output, &(char){ft_i16_abs(value % 10) + '0'}, 1)
	);
}

bool	ft_i32_oprint(t_i32 value, t_output *output)
{
	if (value < 0)
	{
		if (!ft_output_write(output, "-", 1))
			return (false);
	}
	if (value / 10)
	{
		if (!ft_i32_oprint(ft_i32_abs(value / 10), output))
			return (false);
	}
	return (
		ft_output_write(output, &(char){ft_i32_abs(value % 10) + '0'}, 1)
	);
}

bool	ft_i64_oprint(t_i64 value, t_output *output)
{
	if (value < 0)
	{
		if (!ft_output_write(output, "-", 1))
			return (false);
	}
	if (value / 10)
	{
		if (!ft_i64_oprint(ft_i64_abs(value / 10), output))
			return (false);
	}
	return (
		ft_output_write(output, &(char){ft_i64_abs(value % 10) + '0'}, 1)
	);
}
