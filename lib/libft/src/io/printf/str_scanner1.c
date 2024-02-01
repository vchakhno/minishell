/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_scanner1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:15:41 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 08:27:52 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printf.h"

void	ft_str_scanner_init(t_str_scanner *scanner, char *str)
{
	scanner->str = ft_str(str);
	scanner->read_pos = 0;
	scanner->write_pos = 0;
}

bool	ft_str_scanner_has_ended(t_str_scanner *scanner)
{
	return (scanner->read_pos >= scanner->str.len);
}

void	ft_str_scanner_advance(t_str_scanner *scanner)
{
	if (!ft_str_scanner_has_ended(scanner))
		scanner->read_pos++;
}

bool	ft_str_scanner_match(t_str_scanner *scanner, char c)
{
	if (scanner->str.c_str[scanner->read_pos] == c)
	{
		ft_str_scanner_advance(scanner);
		return (true);
	}
	return (false);
}
