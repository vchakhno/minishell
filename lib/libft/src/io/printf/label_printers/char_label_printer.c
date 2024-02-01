/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_label_printer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 20:27:02 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 03:55:09 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printf.h"

void	ft_char_label_printer(t_output *output, va_list args)
{
	ft_output_write_byte(output, va_arg(args, int));
}
