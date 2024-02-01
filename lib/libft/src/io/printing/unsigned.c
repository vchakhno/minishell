/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:53:45 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/22 23:48:40 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printing.h"
#include "libft/io/printf.h"

bool	ft_u8_oprint(t_u8 value, t_output *output)
{
	if (value >= 10)
	{
		if (!ft_u8_oprint(value / 10, output))
			return (false);
	}
	return (ft_output_write(output, &(char){value % 10 + '0'}, 1));
}

bool	ft_u16_oprint(t_u16 value, t_output *output)
{
	if (value >= 10)
	{
		if (!ft_u16_oprint(value / 10, output))
			return (false);
	}
	return (ft_output_write(output, &(char){value % 10 + '0'}, 1));
}

bool	ft_u32_oprint(t_u32 value, t_output *output)
{
	if (value >= 10)
	{
		if (!ft_u32_oprint(value / 10, output))
			return (false);
	}
	return (ft_output_write(output, &(char){value % 10 + '0'}, 1));
}

bool	ft_u64_oprint(t_u64 value, t_output *output)
{
	if (value >= 10)
	{
		if (!ft_u64_oprint(value / 10, output))
			return (false);
	}
	return (ft_output_write(output, &(char){value % 10 + '0'}, 1));
}
