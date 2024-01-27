/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:02:57 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 00:26:22 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "prompts.h"
#include <stdarg.h>

void	print_error(char *error, ...)
{
	va_list	args;

	ft_eprintf("{c_str}", ERROR_PROMPT);
	va_start(args, error);
	ft_voprintf(ft_stderr(), error, args);
	va_end(args);
	ft_eprintln("");
}
