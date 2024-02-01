/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_label_printer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 20:27:02 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 11:04:42 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printf.h"
#include "libft/data/str.h"

void	ft_str_label_printer(t_output *output, va_list args)
{
	ft_str_oprint(va_arg(args, t_str), output);
}
