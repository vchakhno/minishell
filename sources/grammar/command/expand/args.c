/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:45:57 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/27 23:06:10 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	expand_arg(
	t_str src, t_env env, t_u8 exit_status, t_vector *fields_vec
) {
	t_fields	fields;

	init_fields(&fields, fields_vec);
	while (src.len)
	{
		if (!consume_until(&src, "$\"'", &fields))
			return (false);
		if (!src.len)
			break ;
		if (*src.c_str == '$'
			&& !expand_split_var(&src, env, exit_status, &fields))
			return (false);
		else if (*src.c_str == '"'
			&& !expand_dquotes(&src, env, exit_status, &fields))
			return (false);
		else if (*src.c_str == '\'' && !consume_quotes(&src, &fields))
			return (false);
	}
	return (true);
}

bool	expand_args(
	t_vector args, t_env env, t_u8 exit_status, t_vector *raw_fields
) {
	t_u32	i;

	if (!ft_vector_alloc(raw_fields, sizeof(t_string), args.size))
		return (false);
	i = 0;
	while (i < args.size)
	{
		if (!expand_arg(((t_string *)args.elems)[i].str, env, exit_status,
			raw_fields))
		{
			free_fields_vec(*raw_fields);
			return (false);
		}
		i++;
	}
	return (true);
}
