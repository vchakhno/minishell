/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capacity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:59:44 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 12:46:39 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/string.h"
#include "libft/data/mem.h"
#include "libft/arithmetic/bounds.h"
#include <stdlib.h>

bool	ft_string_reserve(t_string *string, t_u32 additionnal)
{
	t_u32	new_capacity;
	char	*new_c_str;

	if (string->len + additionnal + 1 <= string->capacity)
		return (true);
	new_capacity = ft_u32_max(
			string->len + additionnal + 1,
			string->capacity * LIBFT_STRING_GROWTH_FACTOR);
	if (!ft_mem_malloc(&new_c_str, new_capacity))
		return (false);
	ft_mem_copy(new_c_str, string->c_str, string->len + 1);
	free(string->c_str);
	string->c_str = new_c_str;
	string->capacity = new_capacity;
	return (true);
}

bool	ft_string_reserve_exact(t_string *string, t_u32 additionnal)
{
	char	*new_c_str;

	if (string->len + additionnal + 1 <= string->capacity)
		return (true);
	if (!ft_mem_malloc(&new_c_str, string->len + additionnal + 1))
		return (false);
	ft_mem_copy(new_c_str, string->c_str, string->len + 1);
	free(string->c_str);
	string->c_str = new_c_str;
	string->capacity = string->len + additionnal + 1;
	return (true);
}

bool	ft_string_compact(t_string *string)
{
	char	*new_c_str;

	if (string->capacity == string->len + 1)
		return (true);
	if (!ft_mem_dup(&new_c_str, string->c_str, string->len + 1))
		return (false);
	free(string->c_str);
	string->c_str = new_c_str;
	string->capacity = string->len + 1;
	return (true);
}
