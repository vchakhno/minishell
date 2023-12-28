/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:13:01 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/19 21:54:51 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_env_var(t_env_var *var, t_str str)
{
	if (!ft_str_find_char(str, '=', &var->eq_pos))
		return (false);
	return (ft_string_from_str(&var->string, str));
}

t_str	get_env_var_name(t_env_var var)
{
	return (ft_str_get_slice(var.string.str, 0, var.eq_pos));
}

t_str	get_env_var_value(t_env_var var)
{
	return (
		ft_str_get_slice(var.string.str, var.eq_pos + 1,
			var.string.len - var.eq_pos - 1)
	);
}

bool	set_env_var_value(t_env_var *var, t_str value)
{
	var->string.len = var->eq_pos + 1;
	return (ft_string_append_str(&var->string, value));
}

void	free_env_var(t_env_var var)
{
	ft_string_free(var.string);
}
