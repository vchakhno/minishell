/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:21:20 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/23 02:02:25 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

bool	run_builtin_cd(
	t_vector argv, t_session *session, enum e_exec_error *error
) {
	char	*path;

	(void) error;
	if (argv.size == 1)
	{
		print_error("cd: no path argument");
		return (true);
	}
	if (argv.size > 2)
	{
		print_error("cd: too many arguments");
		return (true);
	}
	path = ((t_string *)argv.elems)[1].c_str;
	if (chdir(path) == -1)
	{
		print_error("cd: invalid path");
		print_error("cd: {c_str}", strerror(errno));
		return (true);
	}
	path = getcwd(NULL, 0);
	if (!path || !set_env_var(&session->env, ft_str("PWD"), ft_str(path)))
	{
		free(path);
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
	ft_eprintln("cd successful!");
	return (true);
}
// /media/vchakhno/velo_disk/PC/Travail/42/projects/minishell