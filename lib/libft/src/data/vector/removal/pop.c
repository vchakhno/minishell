/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:03:01 by vchakhno          #+#    #+#             */
/*   Updated: 2023/06/03 20:47:49 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/vector.h"
#include "libft/data/mem.h"

bool	ft_vector_pop(t_vector *vec, void *dest)
{
	return (ft_vector_remove_multiple(vec, vec->size - 1, dest, 1));
}

t_u32	ft_vector_pop_multiple(t_vector *vec, void *dest, t_u32 count)
{
	return (ft_vector_remove_multiple(vec, vec->size - count, dest, count));
}
