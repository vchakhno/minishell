/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:45:57 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/15 23:11:49 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_str	consume_var_name(t_str *src)
{
	t_u32	i;

	advance_str(src, 1);
	if (src->len == 0)
		return (ft_str(""));
	if (src->c_str[0] == '?')
	{
		advance_str(src, 1);
		return (ft_str("?"));
	}
	if (!ft_char_is_alpha(src->c_str[0]))
		return (ft_str(""));
	i = 1;
	while (i < src->len && ft_char_is_alnum(src->c_str[i]))
		i++;
	advance_str(src, i);
	return ((t_str){src->c_str - i, i});
}

bool	expand_exit_status(t_string *value, t_u8 exit_status)
{
	if (!ft_string_alloc(value, 4))
		return (false);
	if (exit_status / 100)
		string_append_char(value, exit_status / 100 + '0');
	if (exit_status / 10)
		string_append_char(value, exit_status / 10 % 10 + '0');
	string_append_char(value, exit_status % 10 + '0');
	return (true);
}

bool	resolve_var_name(
	t_str var_name, t_env env, t_u8 exit_status, t_string *var_value
) {
	t_str	value;

	if (var_name.len == 0)
		return (ft_string_from_c_str(var_value, "$"));
	if (ft_str_equal_c_str(var_name, "?"))
		return (expand_exit_status(var_value, exit_status));
	if (!get_env_var(env, var_name, &value))
		return (ft_string_from_c_str(var_value, ""));
	return (ft_string_from_str(var_value, value));
}

// TODO: remove the double str->string thing with add_field

bool	expand_var(
	t_str *src, t_env env, t_u8 exit_status, t_vector *fields
) {
	t_str		var_name;
	t_string	var_value;

	var_name = consume_var_name(src);
	if (!resolve_var_name(var_name, env, exit_status, &var_value))
		return (false);
	if (!add_field(fields, var_value.str))
	{
		ft_string_free(var_value);
		return (false);
	}
	ft_string_free(var_value);
	return (true);
}
