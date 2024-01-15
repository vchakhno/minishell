/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:45:57 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/15 23:11:13 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	add_field(t_vector *fields, t_str field)
{
	t_string	field_string;

	if (!ft_string_from_str(&field_string, field))
		return (false);
	if (!ft_vector_push(fields, &field_string))
	{
		ft_string_free(field_string);
		return (false);
	}
	return (true);
}

void	free_fields(t_vector fields)
{
	t_u32	i;

	i = 0;
	while (i < fields.size)
	{
		ft_string_free(((t_string *)fields.elems)[i]);
		i++;
	}
	ft_vector_free(fields);
}
