/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:53:45 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/22 23:53:48 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printing.h"
#include "libft/data/str.h"
#include "libft/arithmetic/bounds.h"
#include "libft/arithmetic/float_math.h"
#include "libft/io/printf.h"

bool	ft_cf32_oprint(t_cf32 value, t_output *output)
{
	t_f32	imaginary;

	ft_f32_oprint((t_f32) value, output);
	imaginary = ((t_f32 *)&value)[1];
	if (*(t_u32 *)&imaginary >> 31)
	{
		if (!ft_c_str_oprint(" - ", output))
			return (false);
		imaginary = -imaginary;
	}
	else
	{
		if (!ft_c_str_oprint(" + ", output))
			return (false);
	}
	ft_f32_oprint(imaginary, output);
	if (*(t_u32 *)&imaginary >> 23 == 0xFF)
	{
		if (!ft_c_str_oprint(" * ", output))
			return (false);
	}
	ft_output_write_byte(output, 'i');
	return (true);
}

bool	ft_cf64_oprint(t_cf64 value, t_output *output)
{
	t_f64	imaginary;

	ft_f64_oprint((t_f64) value, output);
	imaginary = ((t_f64 *)&value)[1];
	if (*(t_u64 *)&imaginary >> 63)
	{
		if (!ft_c_str_oprint(" - ", output))
			return (false);
		imaginary = -imaginary;
	}
	else
	{
		if (!ft_c_str_oprint(" + ", output))
			return (false);
	}
	ft_f64_oprint(imaginary, output);
	if (*(t_u64 *)&imaginary >> 52 == 0x7FF)
	{
		if (!ft_c_str_oprint(" * ", output))
			return (false);
	}
	ft_output_write_byte(output, 'i');
	return (true);
}

bool	ft_cf80_oprint(t_cf80 value, t_output *output)
{
	t_f80	imaginary;

	ft_f80_oprint((t_f80) value, output);
	imaginary = ((t_f80 *)&value)[1];
	if (((t_u16 *)&imaginary)[4] >> 15)
	{
		if (!ft_c_str_oprint(" - ", output))
			return (false);
		imaginary = -imaginary;
	}
	else
	{
		if (!ft_c_str_oprint(" + ", output))
			return (false);
	}
	ft_f80_oprint(imaginary, output);
	if (((t_u16 *)&imaginary)[4] == 0x7FFF)
	{
		if (!ft_c_str_oprint(" * ", output))
			return (false);
	}
	ft_output_write_byte(output, 'i');
	return (true);
}

bool	ft_cf128_oprint(t_cf128 value, t_output *output)
{
	t_f128	imaginary;

	ft_f128_oprint((t_f128) value, output);
	imaginary = (t_f128)(value * -1.iq);
	if (((t_u16 *)&imaginary)[7] >> 15)
	{
		if (!ft_c_str_oprint(" - ", output))
			return (false);
		imaginary = -imaginary;
	}
	else
	{
		if (!ft_c_str_oprint(" + ", output))
			return (false);
	}
	ft_f128_oprint(imaginary, output);
	if (((t_u16 *)&imaginary)[7] == 0x7FFF)
	{
		if (!ft_c_str_oprint(" * ", output))
			return (false);
	}
	ft_output_write_byte(output, 'i');
	return (true);
}
