/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_label_printer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 20:27:02 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 11:02:59 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/printf.h"
#include "libft/data/str.h"

static char	**prog_name(void)
{
	static char	*prog_name;

	return (&prog_name);
}

__attribute__((constructor))
static void	get_prog_name(int argc, char **argv)
{
	if (argc == 0)
		*prog_name() = "./a.out";
	else
		*prog_name() = argv[0];
}

void	ft_prog_label_printer(t_output *output, va_list args)
{
	(void) args;
	ft_c_str_oprint(*prog_name(), output);
}
