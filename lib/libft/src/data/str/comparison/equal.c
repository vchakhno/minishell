/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 01:20:06 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 05:20:51 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/str.h"
#include "libft/data/mem.h"
#include <stdbool.h>

bool	ft_str_equal_str(t_str str1, t_str str2)
{
	return (
		str1.len == str2.len
		&& ft_mem_equal(str1.c_str, str2.c_str, str1.len)
	);
}

bool	ft_str_equal_c_str(t_str str1, char *str2)
{
	return (
		str1.len == ft_c_str_len(str2)
		&& ft_mem_equal(str1.c_str, str2, str1.len)
	);
}
