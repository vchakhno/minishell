/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 06:35:00 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 05:55:12 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/string.h"
#include "libft/arithmetic/fixed_types.h"
#include "libft/data/mem.h"

bool	ft_string_remove_c_str_prefix(t_string *string, char *prefix)
{
	t_u32	prefix_len;

	if (ft_str_starts_with_c_str(string->str, prefix))
	{
		prefix_len = ft_c_str_len(prefix);
		ft_string_select_slice(string, prefix_len, string->len - prefix_len);
	}
	return (true);
}

bool	ft_string_remove_str_prefix(t_string *string, t_str prefix)
{
	if (ft_str_starts_with_str(string->str, prefix))
		ft_string_select_slice(string, prefix.len, string->len - prefix.len);
	return (true);
}
