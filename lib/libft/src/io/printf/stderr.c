/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stderr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 04:30:22 by vchakhno          #+#    #+#             */
/*   Updated: 2023/07/24 03:59:37 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printf.h"
#include "libft/io/output.h"
#include <unistd.h>

static t_fd_output	*ft_stderr_raw(void)
{
	static t_fd_output	raw_err;

	return (&raw_err);
}

__attribute__((constructor))
static void	ft_init_stderr(void)
{
	ft_fd_output_init(ft_stderr_raw(), STDERR_FILENO);
}

t_output	*ft_stderr(void)
{
	return (&ft_stderr_raw()->output);
}
