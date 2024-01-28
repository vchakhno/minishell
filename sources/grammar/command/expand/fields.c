/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:45:57 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 08:51:59 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	init_fields(t_fields *fields, t_vector *fields_vec)
{
	fields->fields = fields_vec;
	fields->open = false;
}

bool	get_last_field(t_fields *fields, t_string **field)
{
	t_string	field_string;

	if (!fields->open)
	{
		if (!ft_string_from_c_str(&field_string, ""))
			return (false);
		if (!ft_vector_push(fields->fields, &field_string))
		{
			ft_string_free(field_string);
			return (false);
		}	
		fields->open = true;
	}
	*field = &((t_string *)fields->fields->elems)[fields->fields->size - 1];
	return (true);
}

bool	add_field(t_fields *fields, t_str field)
{
	t_string	*last_field;

	if (!get_last_field(fields, &last_field))
		return (false);
	return (ft_string_append_str(last_field, field));
}

bool	add_u8_field(t_fields *fields, t_u8 field)
{
	t_string	*last_field;

	if (!get_last_field(fields, &last_field))
		return (false);
	if (field >= 100 && !string_append_char(last_field, field / 100 + '0'))
		return (false);
	if (field >= 10 && !string_append_char(last_field, field / 10 % 10 + '0'))
		return (false);
	return (string_append_char(last_field, field % 10 + '0'));
}

void	close_field(t_fields *fields)
{
	fields->open = false;
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
