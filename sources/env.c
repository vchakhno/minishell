/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:13:01 by vchakhno          #+#    #+#             */
/*   Updated: 2023/11/24 08:13:41 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_env_item(t_env_item *item, t_str item_str)
{
	t_u32	sep;

	if (!ft_str_find_char(item_str, '=', &sep))
		return (false);
	if (!ft_string_from_str(&item->key, ft_str_get_slice(item_str, 0, sep)))
		return (false);
	if (!ft_string_from_str(&item->value,
			ft_str_get_slice(item_str, sep + 1, item_str.len - sep - 1)))
	{
		ft_string_free(item->key);
		return (false);
	}
	return (true);
}

bool	parse_env(t_env *env, char **env_strs)
{
	t_u32		len;
	t_u32		i;
	t_env_item	item;

	len = 0;
	while (env_strs[len])
		len++;
	if (!ft_vector_alloc(&env->items, sizeof(t_env_item), len))
		return (false);
	i = 0;
	while (env_strs[i])
	{
		if (!parse_env_item(&item, ft_str(env_strs[i])))
		{
			free_env(env);
			return (false);
		}
		ft_vector_push(&env->items, &item);
		i++;
	}
	return (true);
}

void	display_env(t_env *env)
{
	t_u32	i;

	i = 0;
	while (i < env->items.size)
	{
		ft_println("key: \"{str}\", value: \"{str}\"",
			((t_env_item *)env->items.elems)[i].key.str,
			((t_env_item *)env->items.elems)[i].value.str);
		i++;
	}
}

void	free_env_item(t_env_item *item)
{
	ft_string_free(item->key);
	ft_string_free(item->value);
}

void	free_env(t_env *env)
{
	t_u32	i;

	i = 0;
	while (i < env->items.size)
	{
		free_env_item(&((t_env_item *)env->items.elems)[i]);
		i++;
	}
	ft_vector_free(env->items);
}
