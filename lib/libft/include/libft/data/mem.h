/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 03:58:20 by vchakhno          #+#    #+#             */
/*   Updated: 2023/09/15 23:56:27 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H
# include "libft/data/mem.h"
# undef MEM_H
#else
# ifndef LIBFT_MEM_H
#  define LIBFT_MEM_H

#  include "libft/arithmetic/fixed_types.h"
#  include <stddef.h>
#  include <stdbool.h>

typedef t_u8	t_byte;
typedef void	t_mem;
typedef void	t_ptr;

/******************************************************************************/
/* ALLOCATION																  */
/******************************************************************************/

/*
	WARNING:

	In mem_malloc and mem_calloc, the destination should be **the address**
	of the pointer.
	Example:
	
	int	*array;

	if (!ft_mem_calloc(&array, 5, sizeof(int)))
		return (false);
*/

bool	ft_mem_malloc(t_ptr *ptr, t_u32 size)
		__attribute__((warn_unused_result));
bool	ft_mem_calloc(t_ptr *ptr, t_u32 count, t_u32 size)
		__attribute__((warn_unused_result));
bool	ft_mem_dup(t_ptr *ptr, t_mem *src, t_u32 size)
		__attribute__((warn_unused_result));

/******************************************************************************/
/* COMPARISON																  */
/******************************************************************************/

bool	ft_mem_equal(const t_mem *mem1, const t_mem *mem2,
			t_u32 n);
t_i32	ft_mem_compare(const t_mem *mem1, const t_mem *mem2,
			t_u32 n);

/******************************************************************************/
/* SEARCH																	  */
/******************************************************************************/

bool	ft_mem_find_byte(const t_mem *mem, t_u32 size, t_byte b,
			t_u32 *index);

/******************************************************************************/
/* ASSIGNEMENT																  */
/******************************************************************************/

void	ft_mem_copy(t_mem *dest, const t_mem *src, t_u32 size);
void	ft_mem_move(t_mem *dest, const t_mem *src, t_u32 size);
void	ft_mem_swap(t_mem *mem1, t_mem *mem2, t_u32 size);
void	ft_mem_set(t_mem *mem, t_u32 size, t_byte b);
void	ft_mem_zero(t_mem *mem, t_u32 size);

# endif
#endif