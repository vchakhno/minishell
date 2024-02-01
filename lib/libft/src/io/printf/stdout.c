/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 04:30:22 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 03:50:15 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printf.h"
#include "libft/io/output.h"
#include <unistd.h>

static t_libuf_output	*ft_stdout_libuf(void)
{
	static t_libuf_output	libuf_out;

	return (&libuf_out);
}

__attribute__((constructor))
static void	ft_init_stdout(void)
{
	static t_fd_output	raw_out;
	static char			buffer[FT_STDOUT_BUFFER_SIZE];

	ft_fd_output_init(&raw_out, STDOUT_FILENO);
	ft_libuf_output_init(ft_stdout_libuf(),
		buffer, FT_STDOUT_BUFFER_SIZE, &raw_out.output);
}

__attribute__((destructor))
static void	ft_flush_stdout(void)
{
	ft_libuf_output_flush(ft_stdout_libuf());
}

t_output	*ft_stdout(void)
{
	return (&ft_stdout_libuf()->output);
}
