/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ljust.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:47:55 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 13:20:18 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/string.h"
#include "libft/data/mem.h"

bool	ft_string_ljust(t_string *string, t_u32 size, char filler)
{
	if (string->len >= size)
		return (true);
	if (!ft_string_reserve_exact(string, size - string->len))
		return (false);
	ft_mem_set(string->c_str + string->len, size - string->len, filler);
	string->c_str[size] = '\0';
	string->len = size;
	return (true);
}
