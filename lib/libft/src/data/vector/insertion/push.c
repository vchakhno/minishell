/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 02:33:11 by vchakhno          #+#    #+#             */
/*   Updated: 2023/05/18 12:23:30 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/vector.h"

bool	ft_vector_push(t_vector *vec, void *value)
{
	return (ft_vector_insert_multiple(vec, vec->size, value, 1));
}

bool	ft_vector_push_multiple(t_vector *vec, void *values, t_u32 count)
{
	return (ft_vector_insert_multiple(vec, vec->size, values, count));
}
