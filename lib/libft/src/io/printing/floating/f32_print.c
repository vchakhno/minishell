/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f32_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:53:45 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/22 23:52:22 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printing.h"
#include "libft/data/str.h"
#include "libft/arithmetic/bounds.h"
#include "libft/io/printf.h"
#include "libft/arithmetic/float_math.h"

static bool	ft_f32_print_numerical_part(t_f32 value, t_output *output, t_i8 log)
{
	t_i8	i;
	t_f32	mask;
	t_i8	snapped_log;

	snapped_log = (log - 2 * (log < 0)) / 3 * 3;
	mask = ft_f32_powi(10, log);
	i = 0;
	while (i < 4)
	{
		if (!ft_output_write_byte(
				output, ft_f32_mod(value / mask, 10) + '0'))
			return (false);
		if (log - i < snapped_log
			&& ft_f32_abs(ft_f32_mod(value, mask * 10) < mask / 1000))
			return (true);
		if (log - i == snapped_log)
			if (!ft_output_write(output, ".", 1))
				return (false);
		mask /= 10.000001f;
		i++;
	}
	return (true);
}

bool	ft_f32_oprint(t_f32 value, t_output *output)
{
	t_i8	log;

	if (*(t_u32 *)&value >> 31)
	{
		if (!ft_output_write(output, "-", 1))
			return (false);
		value = -value;
	}
	if (*(t_u32 *)&value == 0xFF << 23)
		return (ft_c_str_oprint("Infinity", output));
	if (*(t_u32 *)&value > 0xFF << 23)
		return (ft_c_str_oprint("NaN", output));
	log = ft_f32_logi(value, 10);
	if (!ft_f32_print_numerical_part(value, output, log))
		return (false);
	if (log < 0 || 3 <= log)
	{
		if (!ft_output_write(output, "e", 1))
			return (false);
		if (!ft_i8_oprint((log - 2 * (log < 0)) / 3 * 3, output))
			return (false);
	}
	return (true);
}
