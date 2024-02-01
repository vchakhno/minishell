/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:32:15 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 03:52:22 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/output.h"
#include "libft/data/str.h"

void	ft_output_init(t_output *output, t_output_write write)
{
	output->write = write;
	output->ended = false;
}

bool	ft_output_has_ended(t_output *output)
{
	return (output->ended);
}

bool	ft_output_write(t_output *output, void *ptr, t_u32 size)
{
	if (!output->write(output, ptr, size))
	{
		output->ended = true;
		return (false);
	}
	return (true);
}

bool	ft_output_write_byte(t_output *output, t_u8 byte)
{
	if (!output->write(output, &byte, 1))
	{
		output->ended = true;
		return (false);
	}
	return (true);
}
