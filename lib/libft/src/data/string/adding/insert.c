/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 07:59:53 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 12:49:27 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/string.h"
#include "libft/data/mem.h"
#include "libft/arithmetic/bounds.h"
#include <stdlib.h>
#include <stdbool.h>

bool	ft_string_insert_str(t_string *string, t_u32 index, t_str inserted)
{
	t_u32	new_capacity;
	char	*new_c_str;

	if (string->len + inserted.len + 1 <= string->capacity)
		ft_mem_move(string->c_str + index + inserted.len,
			string->c_str + index,
			string->len - index + 1);
	else
	{
		new_capacity = ft_u32_max(
				string->len + inserted.len + 1,
				string->capacity * LIBFT_STRING_GROWTH_FACTOR);
		if (!ft_mem_malloc(&new_c_str, new_capacity))
			return (false);
		ft_mem_copy(new_c_str, string->c_str, index);
		ft_mem_copy(new_c_str + index + inserted.len,
			string->c_str + index,
			string->len - index + 1);
		free(string->c_str);
		string->c_str = new_c_str;
		string->capacity = new_capacity;
	}
	ft_mem_copy(string->c_str + index, inserted.c_str, inserted.len);
	string->len += inserted.len;
	return (true);
}

bool	ft_string_insert_c_str(t_string *string, t_u32 index, char *inserted)
{
	return (ft_string_insert_str(string, index, ft_str(inserted)));
}
