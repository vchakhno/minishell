/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:45:57 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 01:42:40 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	advance_str(t_str *str, t_u32 n)
{
	str->c_str += n;
	str->len -= n;
}

bool	string_append_char(t_string *string, char c)
{
	return (ft_string_append_c_str(string, (char []){c, '\0'}));
}

void	free_fields_vec(t_vector fields)
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
