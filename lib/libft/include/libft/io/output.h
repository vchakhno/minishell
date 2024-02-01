/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:32:27 by vchakhno          #+#    #+#             */
/*   Updated: 2023/08/31 20:56:45 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H
# include "libft/io/output.h"
# undef OUTPUT_H
#else
# ifndef LIBFT_OUTPUT_H
#  define LIBFT_OUTPUT_H

#  include "libft/arithmetic/fixed_types.h"
#  include <stdbool.h>

t_u32	ft_safe_write(int fd, void *ptr, t_u32 size);

/******************************************************************************/
/* OUTPUT BASE																  */
/******************************************************************************/

// (const t_output *output, void *ptr, t_u32 size)
typedef bool			(*t_output_write)();
typedef struct s_output
{
	t_output_write	write;
	bool			ended;
}	t_output;

void	ft_output_init(t_output *output, t_output_write write);
bool	ft_output_has_ended(t_output *output);
bool	ft_output_write(t_output *output, void *ptr, t_u32 size);
bool	ft_output_write_byte(t_output *output, t_u8 byte);

/******************************************************************************/
/* FD_OUTPUT																  */
/******************************************************************************/

/*
	The simplest of output types. Writes to a fd (unbuffered !).
	Maybe I should make it buffered by default?
*/

typedef struct s_fd_output
{
	t_output	output;
	int			fd;
}	t_fd_output;

void	ft_fd_output_init(t_fd_output *output, int fd);
bool	ft_fd_output_write(t_fd_output *output, void *ptr, t_u32 size);

/******************************************************************************/
/* BUFFERED OUTPUT															  */
/******************************************************************************/

/*
	This one is really useful, but I'm afraid multiple will ever get in a row,
	which would just cause unnecessary copies. It's pretty dumb, because only
	files should get a buffer for now. So there are no n-buffered output.

	I should probably change the write so that if the data exceeds the buffer
	size, it is written directly to the underlying output instead of copying
	by chunks.
*/

typedef struct s_buf_output
{
	t_output	output;
	void		*buffer;
	t_u32		capacity;
	t_u32		pos;
	t_output	*dest;
}	t_buf_output;

void	ft_buf_output_init(t_buf_output *output,
			void *buffer, t_u32 buffer_size, t_output *dest);
bool	ft_buf_output_write(t_buf_output *output, void *ptr, t_u32 size);
bool	ft_buf_output_flush(t_buf_output *output);

/******************************************************************************/
/* LINE BUFFERED OUPUT														  */
/******************************************************************************/

/*
	Used for live text output, in stdout.
*/

typedef t_buf_output	t_libuf_output;

void	ft_libuf_output_init(t_libuf_output *output,
			void *buffer, t_u32 buffer_size, t_output *dest);
bool	ft_libuf_output_write(t_libuf_output *output, void *ptr, t_u32 size);
bool	ft_libuf_output_flush(t_libuf_output *output);

# endif
#endif