/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:43:50 by vchakhno          #+#    #+#             */
/*   Updated: 2023/06/29 05:55:59 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_MATH_H
# define FLOAT_MATH_H
# include "libft/arithmetic/float_math.h"
# undef FLOAT_MATH_H
#else
# ifndef LIBFT_FLOAT_MATH_H
#  define LIBFT_FLOAT_MATH_H

#  include "libft/arithmetic/fixed_types.h"

t_f32	ft_f32_trunc(t_f32 value);
t_f32	ft_f32_fract(t_f32 value);
t_i32	ft_f32_logi(t_f32 value, t_f32 base);
t_f32	ft_f32_powi(t_f32 base, t_i32 exponent);
t_f32	ft_f32_mod(t_f32 value, t_f32 mod);

t_f64	ft_f64_trunc(t_f64 value);
t_f64	ft_f64_fract(t_f64 value);
t_i32	ft_f64_logi(t_f64 value, t_f64 base);
t_f64	ft_f64_powi(t_f64 base, t_i32 exponent);
t_f64	ft_f64_mod(t_f64 value, t_f64 mod);

t_f80	ft_f80_trunc(t_f80 value);
t_f80	ft_f80_fract(t_f80 value);
t_i32	ft_f80_logi(t_f80 value, t_f80 base);
t_f80	ft_f80_powi(t_f80 base, t_i32 exponent);
t_f80	ft_f80_mod(t_f80 value, t_f80 mod);

t_f128	ft_f128_trunc(t_f128 value);
t_f128	ft_f128_fract(t_f128 value);
t_i32	ft_f128_logi(t_f128 value, t_f128 base);
t_f128	ft_f128_powi(t_f128 base, t_i32 exponent);
t_f128	ft_f128_mod(t_f128 value, t_f128 mod);

# endif
#endif