/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:41:31 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 10:56:17 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H
# include "libft/data/array.h"
# undef ARRAY_H
#else
# ifndef LIBFT_ARRAY_H
#  define LIBFT_ARRAY_H

#  include <stdbool.h>
#  include "libft/arithmetic/fixed_types.h"
#  include "libft/io/output.h"

typedef struct s_array
{
	void		*elems;
	t_u32		size;
	t_u32		elem_size;
}	t_array;

/******************************************************************************/
/* CREATION																	  */
/******************************************************************************/

t_array	ft_array_from(void *elems, t_u32 elem_size, t_u32 size);
t_array	ft_array_get_slice__unchecked(t_array array, t_u32 start, t_u32 len);
t_array	ft_array_get_slice(t_array array, t_u32 start, t_u32 len);

/******************************************************************************/
/* ACCESSING																  */
/******************************************************************************/

void	*ft_array_at(t_array array, t_u32 i);

/******************************************************************************/
/* SEARCH																	  */
/******************************************************************************/

// (const void *a, const void *b)
typedef bool	(*t_equality_func)();

bool	ft_array_contains(t_array array, void *data, t_equality_func func);
bool	ft_array_find(t_array array,
			void *data, t_equality_func func, t_u32 *index);
bool	ft_array_rfind(t_array array,
			void *data, t_equality_func func, t_u32 *index);
t_u32	ft_array_count(t_array array,
			void *data, t_equality_func func);

/******************************************************************************/
/* ORDERING																	  */
/******************************************************************************/

// (const void *a, const void *b)
// true for a > b
typedef bool	(*t_comparison_func)();

bool	ft_array_max(t_array array,
			t_comparison_func func, void *dest);
bool	ft_array_min(t_array array,
			t_comparison_func func, void *dest);
void	ft_array_sort(t_array array,
			t_comparison_func func);

/******************************************************************************/
/* PRINTING																	  */
/******************************************************************************/

// (const void *elem, t_output *output)
typedef bool	(*t_print_func)();

bool	ft_array_print(t_array array, t_print_func func, char *sep);
bool	ft_array_println(t_array array, t_print_func func, char *sep);
bool	ft_array_oprint(t_array array,
			t_output *output, t_print_func func, char *sep);
bool	ft_array_oprintln(t_array array,
			t_output *output, t_print_func func, char *sep);

# endif
#endif