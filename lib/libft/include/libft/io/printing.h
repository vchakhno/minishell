/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 07:33:00 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/22 23:46:43 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTING_H
# define PRINTING_H
# include "libft/io/printing.h"
# undef PRINTING_H
#else
# ifndef LIBFT_PRINTING_H
#  define LIBFT_PRINTING_H

#  include "libft/arithmetic/fixed_types.h"
#  include "libft/io/output.h"
#  include <stdbool.h>

/******************************************************************************/
/* PRINTING FIXED TYPES														  */
/******************************************************************************/

// Unsigned
bool	ft_u8_oprint(t_u8 value, t_output *output);
bool	ft_u16_oprint(t_u16 value, t_output *output);
bool	ft_u32_oprint(t_u32 value, t_output *output);
bool	ft_u64_oprint(t_u64 value, t_output *output);

// Signed
bool	ft_i8_oprint(t_i8 value, t_output *output);
bool	ft_i16_oprint(t_i16 value, t_output *output);
bool	ft_i32_oprint(t_i32 value, t_output *output);
bool	ft_i64_oprint(t_i64 value, t_output *output);

// Floating

// Prints a floating-point number in a format close to the scientific notation
//	- powers of 10 are multiples of 3
//	- 4 significant numbers maximum
//	- e0 isn't displayed
//	- right zeroes following a zero are ommited

bool	ft_f32_oprint(t_f32 value, t_output *output);
bool	ft_f64_oprint(t_f64 value, t_output *output);
bool	ft_f80_oprint(t_f80 value, t_output *output);
bool	ft_f128_oprint(t_f128 value, t_output *output);

// Complex
bool	ft_cf32_oprint(t_cf32 value, t_output *output);
bool	ft_cf64_oprint(t_cf64 value, t_output *output);
bool	ft_cf80_oprint(t_cf80 value, t_output *output);
bool	ft_cf128_oprint(t_cf128 value, t_output *output);

# endif
#endif