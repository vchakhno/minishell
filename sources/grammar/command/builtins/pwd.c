/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/23 17:23:40 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

bool	run_builtin_pwd(
	t_vector argv, t_session *session, enum e_exec_error *error
) {
	char	*path;

	(void) argv;
	(void) session;
	(void) error;
	path = getcwd(NULL, 0);
	if (!path)
	{
		print_error("{c_str}", strerror(errno));
		*error = EXEC_ERROR_RECOVER;
		return (false);
	}
	ft_println("{c_str}", path);
	free(path);
	return (true);
}
