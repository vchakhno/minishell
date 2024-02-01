/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:32:15 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 03:52:50 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/output.h"

void	ft_fd_output_init(t_fd_output *output, int fd)
{
	ft_output_init(&output->output, ft_fd_output_write);
	output->fd = fd;
}

bool	ft_fd_output_write(t_fd_output *output, void *ptr, t_u32 size)
{
	return (ft_safe_write(output->fd, ptr, size) == size);
}
