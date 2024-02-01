/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstrip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 06:35:00 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 13:01:14 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/string.h"
#include "libft/arithmetic/fixed_types.h"
#include "libft/data/mem.h"

bool	ft_string_lstrip(t_string *string, char *set)
{
	t_str	borrowed_set;
	t_u32	start;

	borrowed_set = ft_str(set);
	start = 0;
	while (start < string->len)
	{
		if (!ft_str_contains_char(borrowed_set, string->c_str[start]))
			break ;
		start++;
	}
	string->len -= start;
	ft_mem_copy(string->c_str, string->c_str + start, string->len + 1);
	return (true);
}
