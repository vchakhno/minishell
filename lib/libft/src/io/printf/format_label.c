/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 04:30:22 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/23 00:13:03 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printf.h"

bool	ft_match_label_types(t_str_scanner *scanner, t_label_printer *printer)
{
	static t_label_info	map[] = {{"bool", ft_bool_label_printer},
	{"char", ft_char_label_printer}, {"prog", ft_prog_label_printer},
	{"str", ft_str_label_printer}, {"c_str", ft_c_str_label_printer},
	{"i8", ft_i8_label_printer}, {"i16", ft_i16_label_printer},
	{"i32", ft_i32_label_printer}, {"i64", ft_i64_label_printer},
	{"u8", ft_u8_label_printer}, {"u16", ft_u16_label_printer},
	{"u32", ft_u32_label_printer}, {"u64", ft_u64_label_printer},
	{"f32", ft_f32_label_printer}, {"f64", ft_f64_label_printer},
	{"f80", ft_f80_label_printer}, {"f128", ft_f128_label_printer},
	{"cf32", ft_cf32_label_printer}, {"cf64", ft_cf64_label_printer},
	{"cf80", ft_cf80_label_printer}, {"cf128", ft_cf128_label_printer},
	};
	int					i;

	i = 0;
	while (i < (int)(sizeof(map) / sizeof(*map)))
	{
		if (ft_str_scanner_match_c_str(scanner, map[i].name))
		{
			*printer = map[i].printer;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	ft_parse_label(t_str_scanner *scanner, t_label_printer *printer)
{
	if (!ft_match_label_types(scanner, printer))
		return (false);
	if (!ft_str_scanner_match(scanner, '}'))
		return (false);
	return (true);
}

void	ft_try_print_label(
	t_output *output, t_str_scanner *scanner, va_list args
) {
	t_label_printer	printer;

	if (ft_parse_label(scanner, &printer))
	{
		ft_str_scanner_discard(scanner);
		printer(output, args);
	}
	else
	{
		ft_str_scanner_write(scanner, output);
	}
}
