/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 05:47:25 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SESSION_H
# define SESSION_H

# include "shell_input.h"
# include "runtime_context.h"
# include "grammar.h"
# include <stdbool.h>
# include <libft/libft.h>

typedef struct s_session
{
	t_shell_input		shell_input;
	t_runtime_context	runtime_context;
}	t_session;

bool	setup_session(t_session *session, char **env);
t_u8	run_repl(t_session *session);
void	quit_session(t_session session);

bool	get_incomplete_ast(t_shell_input *input, t_ast_root *ast,
			bool *complete);
bool	get_complete_ast(t_shell_input *input, t_ast_root *ast);

#endif