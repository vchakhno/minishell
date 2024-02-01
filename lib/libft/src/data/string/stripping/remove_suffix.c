/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_suffix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 06:35:00 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 13:02:34 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/string.h"
#include "libft/data/mem.h"

bool	ft_string_remove_c_str_suffix(t_string *string, char *suffix)
{
	if (ft_str_ends_with_c_str(string->str, suffix))
	{
		string->len -= ft_c_str_len(suffix);
		string->c_str[string->len] = '\0';
	}
	return (true);
}

bool	ft_string_remove_str_suffix(t_string *string, t_str suffix)
{
	if (ft_str_ends_with_str(string->str, suffix))
	{
		string->len -= suffix.len;
		string->c_str[string->len] = '\0';
	}
	return (true);
}
