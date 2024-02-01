/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:32:27 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/30 16:59:31 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include "libft/io/input.h"
# undef INPUT_H
#else
# ifndef LIBFT_INPUT_H
#  define LIBFT_INPUT_H

#  include "libft/arithmetic/fixed_types.h"
#  include "libft/data/string.h"
#  include <stdbool.h>

/******************************************************************************/
/* INPUT BASE																  */
/******************************************************************************/

// (const t_input *input, void *ptr, t_u32 capacity, t_u32 *out_size)
typedef bool		(*t_input_read_upto)();
typedef struct s_input
{
	t_input_read_upto	read_upto;
	bool				ended;
}	t_input;

void	ft_input_init(t_input *input, t_input_read_upto read_upto);
bool	ft_input_has_ended(t_input *input);
bool	ft_input_read(t_input *input, void *ptr, t_u32 size);
bool	ft_input_read_upto(\
	t_input *input, void *ptr, t_u32 capacity, t_u32 *out_size\
);
bool	ft_input_read_byte(t_input *input, t_u8 *byte);

/******************************************************************************/
/* FD_INPUT																	  */
/******************************************************************************/

typedef struct s_fd_input
{
	t_input		input;
	int			fd;
}	t_fd_input;

void	ft_fd_input_init(t_fd_input *input, int fd);
bool	ft_fd_input_read_upto(\
	t_fd_input *input, void *ptr, t_u32 capacity, t_u32 *out_size\
);

/******************************************************************************/
/* BUFFERED INPUT															  */
/******************************************************************************/

typedef struct s_buf_input
{
	t_input		input;
	void		*buffer;
	t_u32		capacity;
	t_u32		pos;
	t_u32		size;
	t_input		*source;
}	t_buf_input;

void	ft_buf_input_init(t_buf_input *input,
			void *buffer, t_u32 buffer_size, t_input *source);
bool	ft_buf_input_read_upto(\
	t_buf_input *input, void *ptr, t_u32 max_size, t_u32 *out_size\
);

void	ft_buf_input_read_upto__from_buf(\
	t_buf_input *input, void *ptr, t_u32 max_size, t_u32 *out_size\
);
bool	ft_buf_input_read_upto__from_source(\
	t_buf_input *input, void *ptr, t_u32 max_size, t_u32 *out_size\
);

# endif
#endif