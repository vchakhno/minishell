/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:57:19 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 13:11:37 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/string.h"
#include "libft/data/mem.h"
#include <stdlib.h>

bool	ft_string_alloc(t_string *string, t_u32 capacity)
{
	if (!ft_mem_malloc(&string->c_str, capacity))
		return (false);
	string->len = 0;
	string->capacity = capacity;
	return (true);
}

bool	ft_string_from_str(t_string *string, t_str str)
{
	if (!ft_mem_malloc(&string->c_str, str.len + 1))
		return (false);
	ft_mem_copy(string->c_str, str.c_str, str.len);
	string->c_str[str.len] = '\0';
	string->len = str.len;
	string->capacity = str.len + 1;
	return (true);
}

bool	ft_string_from_c_str(t_string *string, char *c_str)
{
	return (ft_string_from_str(string, ft_str(c_str)));
}

void	ft_string_free(t_string string)
{
	free(string.c_str);
}
