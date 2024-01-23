/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:45:57 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/22 23:15:43 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	expand_until(t_str *str, char *delim, t_fields *fields)
{
	t_u32	i;

	i = 0;
	while (i < str->len && !ft_str_contains_char(ft_str(delim), str->c_str[i]))
		i++;
	if (i && !add_field(fields, (t_str){str->c_str, i}))
		return (false);
	advance_str(str, i);
	return (true);
}

bool	expand_dquotes(
	t_str *str, t_env env, t_u8 exit_status, t_fields *fields
) {
	advance_str(str, 1);
	while (str->len && *str->c_str != '"')
	{
		if (!expand_until(str, "\"$", fields))
			return (false);
		if (*str->c_str == '"')
			break ;
		if (!expand_dquote_var(str, env, exit_status, fields))
			return (false);
	}
	advance_str(str, 1);
	return (true);
}

bool	expand_quotes(t_str *str, t_fields *fields)
{
	t_u32	i;

	advance_str(str, 1);
	i = 0;
	while (i < str->len && str->c_str[i] != '\'')
		i++;
	if (!add_field(fields, (t_str){str->c_str, i}))
		return (false);
	advance_str(str, i + 1);
	return (true);
}

bool	expand(
	t_str src, t_env env, t_u8 exit_status, t_vector *fields_vec
) {
	t_fields	fields;

	init_fields(&fields, fields_vec);
	while (src.len)
	{
		if (!expand_until(&src, "$\"'", &fields))
			return (false);
		if (!src.len)
			break ;
		if (*src.c_str == '$'
			&& !expand_text_var(&src, env, exit_status, &fields))
			return (false);
		else if (*src.c_str == '"'
			&& !expand_dquotes(&src, env, exit_status, &fields))
			return (false);
		else if (*src.c_str == '\'' && !expand_quotes(&src, &fields))
			return (false);
	}
	return (true);
}

bool	expand_all(
	t_vector strings, t_env env, t_u8 exit_status, t_vector *raw_fields
) {
	t_u32	i;

	if (!ft_vector_alloc(raw_fields, sizeof(t_string), strings.size))
		return (false);
	i = 0;
	while (i < strings.size)
	{
		if (!expand(((t_string *)strings.elems)[i].str, env, exit_status,
			raw_fields))
		{
			free_fields_vec(*raw_fields);
			return (false);
		}
		i++;
	}
	return (true);
}
