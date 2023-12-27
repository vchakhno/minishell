/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:45:57 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/27 11:52:41 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	close_field(t_vector *closed_fields, t_string *open_field)
{
	t_string	new_open_field;

	if (open_field->len == 0)
		return (true);
	if (!ft_string_alloc(&new_open_field, 30))
		return (false);
	if (!ft_vector_push(closed_fields, open_field))
	{
		ft_string_free(new_open_field);
		return (false);
	}
	*open_field = new_open_field;
	return (true);
}

bool	split_field(
	t_str pre_split, t_vector *closed_fields, t_string *open_field
) {
	t_u32	block_start;
	t_u32	i;

	block_start = 0;
	i = 0;
	while (i < pre_split.len
		&& !ft_str_contains_char(ft_str("\'\""), pre_split.c_str[i]))
	{
		if (pre_split.c_str[i] == ' ')
		{
			if (!ft_string_append_str(open_field,
					ft_str_get_slice(pre_split, block_start, i - block_start)))
				return (false);
			if (!close_field(closed_fields, open_field))
				return (false);
			block_start = i + 1;
		}
		i++;
	}
	return (ft_string_append_str(open_field,
			ft_str_get_slice(pre_split, block_start, i - block_start)));
}

bool	expand_quotes(
	char **cursor, t_string *open_field
) {
	t_u32	i;

	(*cursor)++;
	i = 0;
	while ((*cursor)[i] != '\'')
		i++;
	if (!ft_string_append_str(open_field, (t_str){(*cursor), i}))
		return (false);
	*cursor += i + 1;
	return (true);
}

bool	expand_dquotes(
	char **cursor, t_env env, t_string *open_field
) {
	(*cursor)++;
	if (!expand_vars(cursor, env, open_field, "\""))
		return (false);
	(*cursor)++;
	return (true);
}

bool	expand_vars(
	char **cursor, t_env env, t_string *open_field, char *delim
) {
	t_u32	block_start;
	t_str	var_value;
	t_u32	i;

	block_start = 0;
	i = 0;
	while ((*cursor)[i] && !ft_str_contains_char(ft_str(delim), (*cursor)[i]))
	{
		if ((*cursor)[i] == '$')
		{
			if (!ft_string_append_str(open_field,
					(t_str){(*cursor) + block_start, i - block_start}))
				return (false);
			i++;
			block_start = i;
			while ((*cursor)[i]
				&& !ft_str_contains_char(ft_str(" \'\"$"), (*cursor)[i]))
				i++;
			if (get_env_var(env,
					(t_str){(*cursor) + block_start, i - block_start},
				&var_value))
				if (!ft_string_append_str(open_field, var_value))
					return (false);
			block_start = i;
		}
		else
			i++;
	}
	if (!ft_string_append_str(open_field,
			(t_str){(*cursor) + block_start, i - block_start}))
		return (false);
	*cursor += i;
	return (true);
}

// Must be null-terminated
bool	expand(t_str str, t_env env, t_vector *closed_fields)
{
	char		*cursor;
	t_string	open_field;
	t_string	pre_split;

	cursor = str.c_str;
	if (!ft_string_alloc(&open_field, 30))
		return (false);
	if (!ft_string_alloc(&pre_split, 30))
		return (false);
	while (*cursor)
	{
		if (*cursor == '\'')
		{
			if (!expand_quotes(&cursor, &open_field))
			{
				ft_string_free(pre_split);
				ft_string_free(open_field);
				return (false);
			}
		}
		else if (*cursor == '\"')
		{
			if (!expand_dquotes(&cursor, env, &open_field))
			{
				ft_string_free(pre_split);
				ft_string_free(open_field);
				return (false);
			}
		}
		else
		{
			if (!expand_vars(&cursor, env, &pre_split, "\'\"")
				|| !split_field(pre_split.str, closed_fields, &open_field))
			{
				ft_string_free(pre_split);
				ft_string_free(open_field);
				return (false);
			}
			pre_split.len = 0;
			pre_split.c_str[0] = '\0';
		}
	}
	ft_string_free(pre_split);
	if (open_field.len != 0)
	{
		if (!ft_vector_push(closed_fields, &open_field))
		{
			ft_string_free(open_field);
			return (false);
		}
	}
	return (true);
}

void	free_fields(t_vector fields)
{
	t_u32	i;

	i = 0;
	while (i < fields.size)
	{
		ft_string_free(((t_string *)fields.elems)[i]);
		i++;
	}
	ft_vector_free(fields);
}

void	display_fields(t_vector fields)
{
	t_u32	i;

	ft_println("Field count: {u32}", fields.size);
	i = 0;
	while (i < fields.size)
	{
		ft_println("Field: {str}", ((t_string *)fields.elems)[i].str);
		i++;
	}
}

// Will be changed to strs later when adapting simple_command's AST
bool	expand_all(t_vector strings, t_env env, t_vector *fields)
{
	t_u32	i;

	if (!ft_vector_alloc(fields, sizeof(t_string), strings.size))
		return (false);
	i = 0;
	while (i < strings.size)
	{
		if (!expand(((t_string *)strings.elems)[i].str, env, fields))
		{
			free_fields(*fields);
			return (false);
		}
		i++;
	}
	display_fields(*fields);
	return (true);
}
