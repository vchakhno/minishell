/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:47:55 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 12:56:15 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/string.h"
#include "libft/arithmetic/fixed_types.h"
#include "libft/data/mem.h"
#include <stdlib.h>

bool	ft_string_center(t_string *string, t_u32 size, char filler)
{
	char	*new_c_str;
	t_u32	left_margin;
	t_u32	right_margin;

	if (string->len >= size)
		return (true);
	left_margin = (size - string->len) / 2;
	if (size + 1 > string->capacity)
	{
		if (!ft_mem_malloc(&new_c_str, size + 1))
			return (false);
		string->capacity = size + 1;
		ft_mem_copy(new_c_str + left_margin, string->c_str, string->len);
		free(string->c_str);
		string->c_str = new_c_str;
	}
	else
		ft_mem_move(string->c_str + left_margin, string->c_str, string->len);
	ft_mem_set(string->c_str, left_margin, filler);
	right_margin = (size - string->len + 1) / 2;
	ft_mem_set(string->c_str + size - right_margin, right_margin, filler);
	string->c_str[size] = '\0';
	string->len = size;
	return (true);
}
