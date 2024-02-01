/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 07:59:53 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 15:26:48 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/string.h"
#include "libft/data/mem.h"

bool	ft_string_append_str(t_string *string, t_str suffix)
{
	if (!ft_string_reserve(string, suffix.len))
		return (false);
	ft_mem_copy(string->c_str + string->len, suffix.c_str, suffix.len);
	string->c_str[string->len + suffix.len] = '\0';
	string->len += suffix.len;
	return (true);
}

bool	ft_string_append_c_str(t_string *string, char *suffix)
{
	return (ft_string_append_str(string, ft_str(suffix)));
}
