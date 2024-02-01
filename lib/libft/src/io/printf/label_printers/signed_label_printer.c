/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed_label_printer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 20:27:02 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 11:04:34 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printf.h"
#include "libft/io/printing.h"
#include "libft/arithmetic/fixed_types.h"

void	ft_i8_label_printer(t_output *output, va_list args)
{
	ft_i8_oprint(va_arg(args, t_i32), output);
}

void	ft_i16_label_printer(t_output *output, va_list args)
{
	ft_i16_oprint(va_arg(args, t_i32), output);
}

void	ft_i32_label_printer(t_output *output, va_list args)
{
	ft_i32_oprint(va_arg(args, t_i32), output);
}

void	ft_i64_label_printer(t_output *output, va_list args)
{
	ft_i64_oprint(va_arg(args, t_i64), output);
}
