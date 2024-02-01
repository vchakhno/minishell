/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_upper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:25:44 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 04:52:28 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/str.h"
#include "libft/arithmetic/fixed_types.h"
#include "libft/data/char.h"
#include <stdbool.h>

bool	ft_str_is_upper(t_str str)
{
	t_u32	i;

	i = 0;
	while (i < str.len)
	{
		if (!ft_char_is_upper(str.c_str[i]))
			return (false);
		i++;
	}
	return (true);
}
