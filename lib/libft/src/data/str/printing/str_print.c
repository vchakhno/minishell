/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:07:24 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 11:31:16 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/str.h"
#include "libft/io/output.h"
#include "libft/io/printf.h"

bool	ft_str_print(t_str str)
{
	return (ft_str_oprint(str, ft_stdout()));
}

bool	ft_str_println(t_str str)
{
	return (ft_str_oprintln(str, ft_stdout()));
}

bool	ft_str_oprint(t_str str, t_output *output)
{
	return (ft_output_write(output, str.c_str, str.len));
}

bool	ft_str_oprintln(t_str str, t_output *output)
{
	if (!ft_str_oprint(str, output))
		return (false);
	return (ft_output_write(output, "\n", 1));
}
