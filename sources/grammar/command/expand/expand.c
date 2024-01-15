/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:45:57 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/15 23:12:25 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	expand(
	t_str src, t_env env, t_u8 exit_status, t_vector *fields
) {
	t_u32	i;

	i = 0;
	while (i < src.len)
	{
		if (src.c_str[i] == '$')
		{
			if (i != 0 && !add_field(fields, (t_str){src.c_str, i}))
				return (false);
			advance_str(&src, i);
			i = 0;
			if (!expand_var(&src, env, exit_status, fields))
				return (false);
		}
		else
			i++;
	}
	if (i != 0 && !add_field(fields, (t_str){src.c_str, i}))
		return (false);
	return (true);
}

bool	expand_all(
	t_vector strings, t_env env, t_u8 exit_status, t_vector *fields
) {
	t_u32	i;

	if (!ft_vector_alloc(fields, sizeof(t_string), strings.size))
		return (false);
	i = 0;
	while (i < strings.size)
	{
		if (!expand(((t_string *)strings.elems)[i].str, env, exit_status,
			fields))
		{
			free_fields(*fields);
			return (false);
		}
		i++;
	}
	return (true);
}
