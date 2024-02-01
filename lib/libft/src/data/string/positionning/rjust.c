/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rjust.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:47:55 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 12:59:08 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/string.h"
#include "libft/data/mem.h"
#include <stdlib.h>

bool	ft_string_rjust(t_string *string, t_u32 size, char filler)
{
	char	*new_c_str;

	if (string->len >= size)
		return (true);
	if (size + 1 > string->capacity)
	{
		if (!ft_mem_malloc(&new_c_str, size + 1))
			return (false);
		string->capacity = size + 1;
		ft_mem_copy(
			new_c_str + size - string->len,
			string->c_str, string->len + 1);
		free(string->c_str);
		string->c_str = new_c_str;
	}
	else
	{
		ft_mem_move(
			string->c_str + size - string->len,
			string->c_str, string->len + 1);
	}
	ft_mem_set(string->c_str, size - string->len, filler);
	string->len = size;
	return (true);
}
