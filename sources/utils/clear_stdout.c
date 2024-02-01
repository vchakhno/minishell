/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_stdout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:12:44 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 04:05:25 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	clear_stdout(void)
{
	t_buf_output	*out;

	out = (t_buf_output *)ft_stdout();
	ft_buf_output_flush(out);
	out->pos = 0;
	out->output.ended = false;
	out->dest->ended = false;
}
