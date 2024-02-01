/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:21:17 by vchakhno          #+#    #+#             */
/*   Updated: 2023/06/23 03:22:47 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOUNDS_H
# define BOUNDS_H
# include "libft/arithmetic/bounds.h"
# undef BOUNDS_H
#else
# ifndef LIBFT_BOUNDS_H
#  define LIBFT_BOUNDS_H

#  include "libft/arithmetic/fixed_types.h"

/******************************************************************************/
/* MIN																		  */
/******************************************************************************/

// Unsigned
t_u8	ft_u8_min(t_u8 a, t_u8 b);
t_u16	ft_u16_min(t_u16 a, t_u16 b);
t_u32	ft_u32_min(t_u32 a, t_u32 b);
t_u64	ft_u64_min(t_u64 a, t_u64 b);

// Signed
t_i8	ft_i8_min(t_i8 a, t_i8 b);
t_i16	ft_i16_min(t_i16 a, t_i16 b);
t_i32	ft_i32_min(t_i32 a, t_i32 b);
t_i64	ft_i64_min(t_i64 a, t_i64 b);

// Floating
t_f32	ft_f32_min(t_f32 a, t_f32 b);
t_f64	ft_f64_min(t_f64 a, t_f64 b);
t_f80	ft_f80_min(t_f80 a, t_f80 b);
t_f128	ft_f128_min(t_f128 a, t_f128 b);

/******************************************************************************/
/* MAX																		  */
/******************************************************************************/

// Unsigned
t_u8	ft_u8_max(t_u8 a, t_u8 b);
t_u16	ft_u16_max(t_u16 a, t_u16 b);
t_u32	ft_u32_max(t_u32 a, t_u32 b);
t_u64	ft_u64_max(t_u64 a, t_u64 b);

// Signed
t_i8	ft_i8_max(t_i8 a, t_i8 b);
t_i16	ft_i16_max(t_i16 a, t_i16 b);
t_i32	ft_i32_max(t_i32 a, t_i32 b);
t_i64	ft_i64_max(t_i64 a, t_i64 b);

// Floating
t_f32	ft_f32_max(t_f32 a, t_f32 b);
t_f64	ft_f64_max(t_f64 a, t_f64 b);
t_f80	ft_f80_max(t_f80 a, t_f80 b);
t_f128	ft_f128_max(t_f128 a, t_f128 b);

/******************************************************************************/
/* CLAMP																	  */
/******************************************************************************/

// Unsigned
t_u8	ft_u8_clamp(t_u8 min, t_u8 value, t_u8 max);
t_u16	ft_u16_clamp(t_u16 min, t_u16 value, t_u16 max);
t_u32	ft_u32_clamp(t_u32 min, t_u32 value, t_u32 max);
t_u64	ft_u64_clamp(t_u64 min, t_u64 value, t_u64 max);

// Signed
t_i8	ft_i8_clamp(t_i8 min, t_i8 value, t_i8 max);
t_i16	ft_i16_clamp(t_i16 min, t_i16 value, t_i16 max);
t_i32	ft_i32_clamp(t_i32 min, t_i32 value, t_i32 max);
t_i64	ft_i64_clamp(t_i64 min, t_i64 value, t_i64 max);

// Floating
t_f32	ft_f32_clamp(t_f32 min, t_f32 value, t_f32 max);
t_f64	ft_f64_clamp(t_f64 min, t_f64 value, t_f64 max);
t_f80	ft_f80_clamp(t_f80 min, t_f80 value, t_f80 max);
t_f128	ft_f128_clamp(t_f128 min, t_f128 value, t_f128 max);

/******************************************************************************/
/* ABS																		  */
/******************************************************************************/

// Signed
t_u8	ft_i8_abs(t_i8 value);
t_u16	ft_i16_abs(t_i16 value);
t_u32	ft_i32_abs(t_i32 value);
t_u64	ft_i64_abs(t_i64 value);

// Floating
t_f32	ft_f32_abs(t_f32 value);
t_f64	ft_f64_abs(t_f64 value);
t_f80	ft_f80_abs(t_f80 value);
t_f128	ft_f128_abs(t_f128 value);

# endif
#endif