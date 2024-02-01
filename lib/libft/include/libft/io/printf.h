/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:42:55 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 03:50:44 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include "libft/io/printf.h"
# undef PRINTF_H
#else
# ifndef LIBFT_PRINTF_H
#  define LIBFT_PRINTF_H

#  include "libft/io/output.h"
#  include "libft/data/str.h"
#  include <stddef.h>
#  include <stdbool.h>
#  include <stdarg.h>

void		ft_printf(char *format, ...);
void		ft_println(char *format, ...);
void		ft_eprintf(char *format, ...);
void		ft_eprintln(char *format, ...);
void		ft_oprintf(t_output *output, char *format, ...);
void		ft_oprintln(t_output *output, char *format, ...);
void		ft_voprintf(t_output *output, char *format, va_list args);

#  define FT_STDOUT_BUFFER_SIZE	1024

t_output	*ft_stdout(void);
t_output	*ft_stderr(void);

typedef struct s_str_scanner
{
	t_str	str;
	t_u32	read_pos;
	t_u32	write_pos;
}	t_str_scanner;

void		ft_str_scanner_init(t_str_scanner *scanner, char *str);
bool		ft_str_scanner_has_ended(t_str_scanner *scanner);
void		ft_str_scanner_advance(t_str_scanner *scanner);
void		ft_str_scanner_discard(t_str_scanner *scanner);
bool		ft_str_scanner_match(t_str_scanner *scanner, char c);
bool		ft_str_scanner_match_c_str(
				t_str_scanner *scanner, char *c_str);
void		ft_str_scanner_write(t_str_scanner *scanner, t_output *output);

typedef void	(*t_label_printer)(t_output *output, va_list args);
typedef struct s_label_info
{
	char			*name;
	t_label_printer	printer;
}	t_label_info;

void		ft_try_print_label(t_output *output,
				t_str_scanner *scanner, va_list args);

void		ft_bool_label_printer(t_output *output, va_list args);
void		ft_str_label_printer(t_output *output, va_list args);
void		ft_c_str_label_printer(t_output *output, va_list args);
void		ft_char_label_printer(t_output *output, va_list args);
void		ft_i8_label_printer(t_output *output, va_list args);
void		ft_i16_label_printer(t_output *output, va_list args);
void		ft_i32_label_printer(t_output *output, va_list args);
void		ft_i64_label_printer(t_output *output, va_list args);
void		ft_u8_label_printer(t_output *output, va_list args);
void		ft_u16_label_printer(t_output *output, va_list args);
void		ft_u32_label_printer(t_output *output, va_list args);
void		ft_u64_label_printer(t_output *output, va_list args);
void		ft_prog_label_printer(t_output *output, va_list args);
void		ft_f32_label_printer(t_output *output, va_list args);
void		ft_f64_label_printer(t_output *output, va_list args);
void		ft_f80_label_printer(t_output *output, va_list args);
void		ft_f128_label_printer(t_output *output, va_list args);
void		ft_cf32_label_printer(t_output *output, va_list args);
void		ft_cf64_label_printer(t_output *output, va_list args);
void		ft_cf80_label_printer(t_output *output, va_list args);
void		ft_cf128_label_printer(t_output *output, va_list args);

# endif
#endif