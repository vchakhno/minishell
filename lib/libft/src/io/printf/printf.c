/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 04:30:22 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/23 00:04:38 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printf.h"

void	ft_printf(char *format, ...)
{
	va_list			args;

	va_start(args, format);
	ft_voprintf(ft_stdout(), format, args);
	va_end(args);
}

void	ft_println(char *format, ...)
{
	va_list			args;

	va_start(args, format);
	ft_voprintf(ft_stdout(), format, args);
	ft_c_str_print("\n");
	va_end(args);
}
