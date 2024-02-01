/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 01:13:29 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 05:20:44 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/str.h"
#include "libft/arithmetic/fixed_types.h"
#include "libft/arithmetic/bounds.h"
#include "libft/data/mem.h"

t_i32	ft_str_compare_str(t_str str1, t_str str2)
{
	return (
		ft_mem_compare(
			str1.c_str, str2.c_str,
			ft_u32_min(str1.len, str2.len)
		)
	);
}

t_i32	ft_str_compare_c_str(t_str str1, char *str2)
{
	return (
		ft_mem_compare(
			str1.c_str, str2,
			ft_u32_min(str1.len, ft_c_str_len(str2))
		)
	);
}
