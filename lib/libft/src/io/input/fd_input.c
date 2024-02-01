/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:43:33 by vchakhno          #+#    #+#             */
/*   Updated: 2023/08/20 17:16:19 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/input.h"
#include <unistd.h>

void	ft_fd_input_init(t_fd_input *input, int fd)
{
	ft_input_init(&input->input, ft_fd_input_read_upto);
	input->fd = fd;
}

// Maybe check errno

bool	ft_fd_input_read_upto(
	t_fd_input *input, void *ptr, t_u32 capacity, t_u32 *out_size
) {
	ssize_t	read_return;

	read_return = read(input->fd, ptr, capacity);
	if (read_return <= 0)
		return (false);
	*out_size = read_return;
	return (true);
}
