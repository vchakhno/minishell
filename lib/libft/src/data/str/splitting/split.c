/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:04:46 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 08:55:59 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/str.h"
#include "libft/data/iter.h"

bool	ft_str_split_iter_next(t_str_iter *iter, t_str *dest);

t_str_iter	ft_str_split_by_str(t_str str, t_str delim)
{
	return ((t_str_iter){
		.next = ft_str_split_iter_next,
		.remaining = str,
		.delim = delim
	});
}

t_str_iter	ft_str_split_by_c_str(t_str str, char *delim)
{
	return ((t_str_iter){
		.next = ft_str_split_iter_next,
		.remaining = str,
		.delim = ft_str(delim)
	});
}

bool	ft_str_split_iter_next(t_str_iter *iter, t_str *dest)
{
	t_u32	index;

	if (iter->remaining.len == 0)
		return (false);
	if (ft_str_find_str(iter->remaining, iter->delim, &index))
	{
		dest->c_str = iter->remaining.c_str;
		dest->len = index;
		iter->remaining.c_str += index + iter->delim.len;
		iter->remaining.len -= index + iter->delim.len;
	}
	else
	{
		*dest = iter->remaining;
		iter->remaining.c_str += iter->remaining.len;
		iter->remaining.len = 0;
	}
	return (true);
}
