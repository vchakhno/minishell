/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:45:57 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/22 01:09:20 by vchakhno         ###   ########.fr       */
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

bool	expand_var(
	t_str *src, t_env env, t_u8 exit_status, t_fields *fields
) {
	t_str	name;
	t_str	value;

	name = consume_var_name(src);
	if (name.len == 0)
		return (add_field(fields, ft_str("$")));
	if (ft_str_equal_c_str(name, "?"))
		return (add_u8_field(fields, exit_status));
	if (get_env_var(env, name, &value))
		return (add_field(fields, value));
	return (true);
}
