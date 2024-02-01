/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 04:30:22 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/23 00:04:51 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printf.h"

void	ft_oprintf(t_output *output, char *format, ...)
{
	va_list			args;

	va_start(args, format);
	ft_voprintf(output, format, args);
	va_end(args);
}

void	ft_oprintln(t_output *output, char *format, ...)
{
	va_list			args;

	va_start(args, format);
	ft_voprintf(output, format, args);
	ft_output_write(output, "\n", 1);
	va_end(args);
}

void	ft_voprintf(t_output *output, char *format, va_list args)
{
	t_str_scanner	scanner;

	ft_str_scanner_init(&scanner, format);
	while (!ft_str_scanner_has_ended(&scanner)
		&& !ft_output_has_ended(output))
	{
		if (ft_str_scanner_match(&scanner, '{'))
		{
			ft_try_print_label(output, &scanner, args);
		}
		else
		{
			ft_str_scanner_advance(&scanner);
			ft_str_scanner_write(&scanner, output);
		}
	}
}
