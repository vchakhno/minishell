/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:45:57 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 01:09:11 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

bool	consume_until(t_str *str, char *delim, t_fields *fields)
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
	t_str *str, t_runtime_context context, t_fields *fields
) {
	advance_str(str, 1);
	while (str->len && *str->c_str != '"')
	{
		if (!consume_until(str, "\"$", fields))
			return (false);
		if (*str->c_str == '"')
			break ;
		if (!expand_var(str, context, fields))
			return (false);
	}
	advance_str(str, 1);
	return (true);
}

bool	consume_quotes(t_str *str, t_fields *fields)
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
