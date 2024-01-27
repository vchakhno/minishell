/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:23:46 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 00:28:22 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executable.h"
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <unistd.h>

bool	alloc_executable(
	t_executable *exec, t_vector argv, t_env env, t_u8 *exit_status
) {
	if (!find_executable(env, ((t_string *)argv.elems)[0].str,
		&exec->full_path, exit_status))
		return (false);
	if (!compact_argv(&exec->compact_argv, argv))
	{
		ft_string_free(exec->full_path);
		*exit_status = 1;
		return (false);
	}
	if (!compact_env(&exec->compact_env, env))
	{
		ft_vector_free(exec->compact_argv);
		ft_string_free(exec->full_path);
		*exit_status = 1;
		return (false);
	}
	return (true);
}

void	start_executable(t_executable exec)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	execve(
		exec.full_path.c_str,
		(char **)exec.compact_argv.elems,
		(char **)exec.compact_env.elems);
	ft_eprintln("Execve failure");
}

bool	run_executable(
	t_executable exec, t_backup_fds backup, t_u8 *status
) {
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid == -1)
		return (true);
	if (pid == 0)
	{
		discard_backup_fds(backup);
		start_executable(exec);
		return (false);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		*status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		*status = 128 + WTERMSIG(wstatus);
	return (true);
}

void	free_executable(t_executable exec)
{
	ft_vector_free(exec.compact_env);
	ft_vector_free(exec.compact_argv);
	ft_string_free(exec.full_path);
}
