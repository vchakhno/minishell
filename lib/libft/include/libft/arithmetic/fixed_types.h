/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:31:20 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 11:54:16 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_TYPES_H
# define FIXED_TYPES_H
# include "libft/arithmetic/fixed_types.h"
# undef FIXED_TYPES_H
#else
# ifndef LIBFT_FIXED_TYPES_H
#  define LIBFT_FIXED_TYPES_H

#  include <stdint.h>

/******************************************************************************/
/* UNSIGNED																	  */
/******************************************************************************/

typedef uint8_t					t_u8;
typedef uint16_t				t_u16;
typedef uint32_t				t_u32;
typedef uint64_t				t_u64;

/******************************************************************************/
/* SIGNED																	  */
/******************************************************************************/

typedef int8_t					t_i8;
typedef int16_t					t_i16;
typedef int32_t					t_i32;
typedef int64_t					t_i64;

/******************************************************************************/
/* FLOAT																	  */
/******************************************************************************/

typedef float					t_f32;
typedef double					t_f64;
typedef long double				t_f80;
typedef __float128				t_f128;

/******************************************************************************/
/* COMPLEX																	  */
/******************************************************************************/

typedef _Complex float			t_cf32;
typedef _Complex double			t_cf64;
typedef _Complex long double	t_cf80;
__attribute__((mode(TC)))
typedef _Complex float t_cf128;

# endif
#endif