/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_label_printer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 20:27:02 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 11:02:16 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printf.h"
#include "libft/io/printing.h"
#include "libft/arithmetic/fixed_types.h"

void	ft_cf32_label_printer(t_output *output, va_list args)
{
	ft_cf32_oprint(va_arg(args, t_cf32), output);
}

void	ft_cf64_label_printer(t_output *output, va_list args)
{
	ft_cf64_oprint(va_arg(args, t_cf64), output);
}

void	ft_cf80_label_printer(t_output *output, va_list args)
{
	ft_cf80_oprint(va_arg(args, t_cf80), output);
}

void	ft_cf128_label_printer(t_output *output, va_list args)
{
	ft_cf128_oprint(va_arg(args, t_cf128), output);
}
