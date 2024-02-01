/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_lower.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 07:00:48 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 05:19:32 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/str.h"
#include "libft/arithmetic/fixed_types.h"
#include "libft/data/char.h"

void	ft_str_to_lower(t_str str)
{
	t_u32	i;

	i = 0;
	while (i < str.len)
	{
		str.c_str[i] = ft_char_to_lower(str.c_str[i]);
		i++;
	}
}
