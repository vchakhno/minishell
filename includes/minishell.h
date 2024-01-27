/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 00:24:00 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "tokenizer.h"
# include "environment.h"
# include "grammar.h"
# include "executable.h"
# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>
# include <libft/libft.h>
# include <sys/types.h>

/* ************************************************************************** */
/* SESSION																	  */
/* ************************************************************************** */

// also contains terminal settings?

typedef struct s_session
{
	t_lines		lines;
	t_env		env;
	t_u8		exit_status;
}	t_session;

bool	init_session(t_session *session, char **env);
void	run_repl(t_session *session);
void	destroy_session(t_session session);

#endif