/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:42:59 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 08:05:12 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_H
# define ITER_H
# include "libft/data/iter.h"
# undef ITER_H
#else
# ifndef LIBFT_ITER_H
#  define LIBFT_ITER_H

#  include <stdbool.h>

//	(t_iter	*iter, void *dest)
typedef bool	(*t_iter_next)();

typedef struct s_iter
{
	t_iter_next	next;
}	t_iter;

# endif
#endif