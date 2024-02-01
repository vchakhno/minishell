/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_scanner2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:15:41 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 18:22:23 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printf.h"
#include "libft/data/str.h"
#include "libft/data/mem.h"

void	ft_str_scanner_discard(t_str_scanner *scanner)
{
	scanner->write_pos = scanner->read_pos;
}

void	ft_str_scanner_write(t_str_scanner *scanner, t_output *output)
{
	ft_output_write(output,
		scanner->str.c_str + scanner->write_pos,
		scanner->read_pos - scanner->write_pos);
	scanner->write_pos = scanner->read_pos;
}

bool	ft_str_scanner_match_c_str(t_str_scanner *scanner, char *c_str)
{
	t_u32	len;

	len = ft_c_str_len(c_str);
	if (len > scanner->str.len - scanner->read_pos)
		return (false);
	if (ft_mem_equal(scanner->str.c_str + scanner->read_pos,
			c_str, len))
	{
		scanner->read_pos += len;
		return (true);
	}
	return (false);
}
