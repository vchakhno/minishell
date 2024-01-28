/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 01:54:19 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SESSION_H
# define SESSION_H

# include "shell_input.h"
# include "runtime_context.h"
# include <stdbool.h>
# include <libft/libft.h>

typedef struct s_session
{
	t_shell_input		shell_input;
	t_runtime_context	runtime_context;
}	t_session;

bool	init_session(t_session *session, char **env);
t_u8	run_repl(t_session *session);
void	destroy_session(t_session session);

#endif