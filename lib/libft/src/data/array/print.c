/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 08:16:34 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 10:58:06 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/array.h"
#include "libft/io/output.h"
#include "libft/data/str.h"
#include "libft/io/printf.h"

bool	ft_array_print(t_array array, t_print_func func, char *sep)
{
	return (ft_array_oprint(array, ft_stdout(), func, sep));
}

bool	ft_array_println(t_array array, t_print_func func, char *sep)
{
	return (ft_array_oprintln(array, ft_stdout(), func, sep));
}

bool	ft_array_oprint(
	t_array array, t_output *output, t_print_func func, char *sep
) {
	t_u32	i;

	if (!sep)
		sep = ", ";
	ft_output_write_byte(output, '[');
	i = 0;
	while (i < array.size)
	{
		if (!func(ft_array_at(array, i), output)
			|| (i != array.size - 1 && !ft_c_str_oprint(sep, output)))
			return (false);
		i++;
	}
	ft_output_write_byte(output, ']');
	return (true);
}

bool	ft_array_oprintln(
	t_array array, t_output *output, t_print_func func, char *sep
) {
	if (!ft_array_oprint(array, output, func, sep))
		return (false);
	return (ft_output_write_byte(output, '\n'));
}
