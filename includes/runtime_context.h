/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime_context.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:33:30 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 04:00:07 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_CONTEXT_H
# define RUNTIME_CONTEXT_H

# include "environment.h"
# include <libft/libft.h>

typedef struct s_runtime_context
{
	t_env	env;
	t_u8	exit_status;
}	t_runtime_context;

bool	alloc_runtime_context(t_runtime_context *context, char **env);
void	free_runtime_context(t_runtime_context context);

#endif