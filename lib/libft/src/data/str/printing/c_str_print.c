/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_str_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:10:42 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 10:57:54 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/output.h"
#include "libft/data/str.h"
#include "libft/io/printf.h"

bool	ft_c_str_print(char *c_str)
{
	return (ft_c_str_oprint(c_str, ft_stdout()));
}

bool	ft_c_str_println(char *c_str)
{
	return (ft_c_str_oprintln(c_str, ft_stdout()));
}

bool	ft_c_str_oprint(char *c_str, t_output *output)
{
	return (ft_output_write(output, c_str, ft_c_str_len(c_str)));
}

bool	ft_c_str_oprintln(char *c_str, t_output *output)
{
	if (!ft_c_str_oprint(c_str, output))
		return (false);
	return (ft_output_write(output, "\n", 1));
}
