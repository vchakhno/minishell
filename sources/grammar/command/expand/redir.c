/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:45:57 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 03:55:09 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

bool	expand_redir_to_fields(
	t_str filename, t_runtime_context context, t_fields *fields
) {
	while (filename.len)
	{
		if (!consume_until(&filename, "$\"'", fields))
			return (false);
		if (!filename.len)
			break ;
		if (*filename.c_str == '$'
			&& !expand_var(&filename, context, fields))
			return (false);
		else if (*filename.c_str == '"'
			&& !expand_dquotes(&filename, context, fields))
			return (false);
		else if (*filename.c_str == '\'' && !consume_quotes(&filename, fields))
			return (false);
	}
	return (true);
}

// true -> OK (but might not exist)
// false -> malloc error
bool	expand_redir(
	t_str filename, t_runtime_context context, t_string *field, bool *exists
) {
	t_vector	fields_vec;
	t_fields	fields;

	if (!ft_vector_alloc(&fields_vec, sizeof(t_string), 1))
		return (false);
	init_fields(&fields, &fields_vec);
	if (!expand_redir_to_fields(filename, context, &fields)
		|| !fields_vec.size)
	{
		free_fields_vec(fields_vec);
		return (false);
	}
	*exists = fields_vec.size;
	if (!fields_vec.size)
		return (true);
	ft_vector_remove(&fields_vec, 0, field);
	free_fields_vec(fields_vec);
	return (true);
}
