/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_alnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 01:03:14 by vchakhno          #+#    #+#             */
/*   Updated: 2023/05/18 07:22:15 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/data/char.h"

bool	ft_char_is_alnum(char c)
{
	return (ft_char_is_alpha(c) || ft_char_is_digit(c));
}
