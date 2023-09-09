/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekhaled <ekhaled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:15:05 by ekhaled           #+#    #+#             */
/*   Updated: 2023/09/08 17:07:53 by ekhaled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdint.h>

# define SUCCESS 1
# define FAILURE 0

typedef struct s_history
{

}	t_history;

typedef struct s_env
{

}	t_env;

typedef struct s_session
{
	t_history	history;
	t_env		env;
	uint8_t		last_cmd_status;
}	t_session;

#endif