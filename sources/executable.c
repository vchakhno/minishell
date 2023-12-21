/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:23:46 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/19 23:10:26 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

bool	compact_argv(t_vector *compact_argv, t_vector argv)
{
	t_u32	i;

	if (!ft_vector_alloc(compact_argv, sizeof(char *), argv.size + 1))
		return (false);
	i = 0;
	while (i < argv.size)
	{
		ft_vector_push(compact_argv, &((t_string *)argv.elems)[i].c_str);
		i++;
	}
	ft_vector_push(compact_argv, &(char *){NULL});
	return (true);
}

bool	compact_env(t_vector *compact_env, t_env env)
{
	t_env_var	var;
	t_u32		i;

	if (!ft_vector_alloc(compact_env, sizeof(char *), env.vars.size + 1))
		return (false);
	i = 0;
	while (i < env.vars.size)
	{
		var = ((t_env_var *)env.vars.elems)[i];
		ft_vector_push(compact_env, &var.string.c_str);
		i++;
	}
	ft_vector_push(compact_env, &(char *){NULL});
	return (true);
}

bool	alloc_executable(
	t_executable *exec, t_vector argv, t_env env, enum e_exec_error *error
) {
	if (!find_executable(env, ((t_string *)argv.elems)[0].str, &exec->full_path,
		error))
		return (false);
	if (!compact_argv(&exec->compact_argv, argv))
	{
		*error = EXEC_ERROR_EXIT;
		ft_string_free(exec->full_path);
		return (false);
	}
	if (!compact_env(&exec->compact_env, env))
	{
		*error = EXEC_ERROR_EXIT;
		ft_vector_free(exec->compact_argv);
		ft_string_free(exec->full_path);
		return (false);
	}
	return (true);
}

bool	run_executable(t_executable exec, enum e_exec_error *error)
{
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid == -1)
	{
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
	if (pid == 0)
	{
		execve(
			exec.full_path.c_str,
			(char **)exec.compact_argv.elems,
			(char **)exec.compact_env.elems);
		*error = EXEC_ERROR_EXIT;
		ft_println("Execve failure");
		return (false);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		ft_println("Status: {u32}", WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		ft_println("Signaled: {u32}", WTERMSIG(wstatus));
	return (true);
}

void	free_executable(t_executable exec)
{
	ft_vector_free(exec.compact_env);
	ft_vector_free(exec.compact_argv);
	ft_string_free(exec.full_path);
}