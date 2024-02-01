/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_slice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 01:02:00 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 12:53:07 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/string.h"
#include "libft/data/mem.h"

void	ft_string_select_slice(t_string *string, t_u32 start, t_u32 len)
{
	ft_mem_copy(string->c_str, string->c_str + start, len);
	string->c_str[len] = '\0';
	string->len = len;
}
