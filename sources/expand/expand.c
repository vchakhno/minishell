/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:45:57 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/26 03:53:33 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// first space
//   append to current
//
// other spaces
//   append current to tokens
//   clear current
//   append to current

bool	expand_text(
	char **cursor, t_env env, t_vector *tokens, t_string *current
) {
	t_u32	i;

	(void) tokens;
	(void) env;
	i = 0;
	while ((*cursor)[i] && !ft_str_contains_char(ft_str(" \'\""), (*cursor)[i]))
		i++;
	if (!ft_string_append_str(current, (t_str){*cursor, i}))
		return (false);
	*cursor += i;
	return (true);
}

// Must be null-terminated
bool	expand(t_str str, t_env env, t_vector *tokens)
{
	char		*cursor;
	t_string	current;

	cursor = str.c_str;
	if (!ft_string_alloc(&current, 30))
		return (false);
	while (*cursor)
	{
		if (*cursor == ' ')
		{
			if (current.len)
			{
				if (!ft_vector_push(tokens, &current))
				{
					ft_string_free(current);
					return (false);
				}
				current.len = 0;
				current.c_str[0] = '\0';
			}
			cursor++;
		}
		else
		{
			if (!expand_text(&cursor, env, tokens, &current))
			{
				ft_string_free(current);
				return (false);
			}
		}
	}
	if (current.len && !ft_vector_push(tokens, &current))
	{
		ft_string_free(current);
		return (false);
	}
	return (true);
}

void	free_tokens(t_vector tokens)
{
	t_u32	i;

	i = 0;
	while (i < tokens.size)
	{
		ft_string_free(((t_string *)tokens.elems)[i]);
		i++;
	}
	ft_vector_free(tokens);
}

// Will be changed to strs later when adapting simple_command's AST
bool	expand_all(t_vector strings, t_env env, t_vector *tokens)
{
	t_u32	i;

	if (!ft_vector_alloc(tokens, sizeof(t_string), strings.size))
		return (false);
	i = 0;
	while (i < strings.size)
	{
		if (!expand(((t_string *)strings.elems)[i].str, env, tokens))
		{
			free_tokens(*tokens);
			return (false);
		}
		i++;
	}
	return (true);
}
