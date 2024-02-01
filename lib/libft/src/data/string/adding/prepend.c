/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 07:59:53 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 12:51:45 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/string.h"
#include "libft/data/mem.h"
#include "libft/arithmetic/bounds.h"
#include <stdlib.h>

bool	ft_string_prepend_str(t_string *string, t_str prefix)
{
	t_u32	new_capacity;
	char	*new_c_str;

	if (string->len + prefix.len + 1 <= string->capacity)
		ft_mem_move(string->c_str + prefix.len, string->c_str, string->len + 1);
	else
	{
		new_capacity = ft_u32_max(
				string->len + prefix.len + 1,
				string->capacity * LIBFT_STRING_GROWTH_FACTOR);
		if (!ft_mem_malloc(&new_c_str, new_capacity))
			return (false);
		ft_mem_copy(new_c_str + prefix.len, string->c_str, string->len + 1);
		free(string->c_str);
		string->c_str = new_c_str;
		string->capacity = new_capacity;
	}
	ft_mem_copy(string->c_str, prefix.c_str, prefix.len);
	string->len += prefix.len;
	return (true);
}

bool	ft_string_prepend_c_str(t_string *string, char *prefix)
{
	return (ft_string_prepend_str(string, ft_str(prefix)));
}
