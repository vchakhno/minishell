/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/02/01 04:05:02 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTABLE_H
# define EXECUTABLE_H

# include "environment.h"
# include "redirections.h"
# include <stdbool.h>
# include <libft/libft.h>

typedef struct s_executable
{
	t_string	full_path;
	t_vector	compact_argv;
	t_vector	compact_env;
}	t_executable;

bool	compact_argv(t_vector *compact_argv, t_vector argv);
bool	compact_env(t_vector *compact_env, t_env env);

bool	find_executable(t_env env, t_str cmd_name, t_string *full_path,
			t_u8 *exit_status);
bool	alloc_executable(t_executable *exec, t_vector argv, t_env env,
			t_u8 *exit_status);
bool	run_executable(t_executable exec, t_backup_fds backup,
			t_u8 *exit_status);
void	free_executable(t_executable exec);

#endif